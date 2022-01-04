#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

class Node {
public:
  int data;
  Node *left;
  Node *right;
  Node(int);
};

Node::Node(int dataval) : data(dataval), left(nullptr), right(nullptr) {}
Node *tree_generate(std::vector<int> &, int, int);
void tree_delete(Node *);
void tree_balance(Node *, std::vector<int> &);
void tree_print_infix(Node *);
void tree_print(Node *, void (*)(Node *));
int tree_get_depth_level(Node *);
int tree_nodes_at_level(Node *, int, int);
std::vector<int> fread();
bool tree_is_valid(std::vector<int> &);
int tree_load_data(std::vector<int> &, std::vector<int> &);

int main() {
  // void (*infix)(Node *) = print_infix;
  bool run = true;
  std::vector<int> balanced, unbalanced;

  if (tree_load_data(balanced, unbalanced) == 1)
    return 1;

  Node *root = tree_generate(balanced, 0, balanced.size() - 1);
  tree_balance(root, unbalanced);
  int depth_level = tree_get_depth_level(root);

  while (run) {
    std::cout << "Depth level of BST is " << depth_level << std::endl;
    for (int i = 0; i < depth_level; i++)
      std::cout << "Depth level " << i + 1 << " -> "
                << tree_nodes_at_level(root, 0, i) << std::endl;
    run = false;
  }

  tree_delete(root);
  return 0;
}

Node *tree_generate(std::vector<int> &balanced, int begin, int end) {
  if (end < begin)
    return nullptr;

  int sum = begin + end;
  int middle = (sum + (sum % 2 != 0)) / 2;
  Node *root = new Node(balanced.at(middle--));
  root->left = tree_generate(balanced, begin, middle++);
  root->right = tree_generate(balanced, ++middle, end);
  return root;
}

void tree_delete(Node *root) {
  if (root == nullptr)
    return;

  tree_delete(root->left);
  tree_delete(root->right);
  delete root;
  return;
}

void tree_balance(Node *root, std::vector<int> &unbalanced) {
  // needs more testing and optimization
  if (root == nullptr)
    return;

  Node *temp = root;
  while (temp->left->left != nullptr)
    temp = temp->left;
  unbalanced.push_back(temp->left->data);
  std::sort(std::begin(unbalanced), std::end(unbalanced));
  tree_delete(temp->left);
  temp->left = tree_generate(unbalanced, 0, unbalanced.size() - 1);
  return;
}

void tree_print_infix(Node *root) {
  if (root == nullptr)
    return;

  tree_print_infix(root->left);
  std::cout << root->data << " ";
  tree_print_infix(root->right);
  return;
}

void tree_print(Node *root, void (*function)(Node *)) {
  (*function)(root);
  std::cout << std::endl;
  return;
}

std::vector<int> fread() {
  // i probably should add exception handling
  std::vector<int> seed;
  std::ifstream fin("input.txt");
  std::istream_iterator<int> in(fin);
  std::copy(in, std::istream_iterator<int>(), std::back_inserter(seed));
  fin.close();
  return seed;
}

int tree_get_depth_level(Node *root) {
  if (root == nullptr)
    return 0;

  int left = tree_get_depth_level(root->left);
  int right = tree_get_depth_level(root->right);

  return right < left ? left + 1 : right + 1;
}

int tree_nodes_at_level(Node *root, int level, int target) {
  if (root == nullptr)
    return 0;

  if (level == target)
    return 1;

  return tree_nodes_at_level(root->left, level + 1, target) +
         tree_nodes_at_level(root->right, level + 1, target);
}

bool tree_is_valid(std::vector<int> &seed) {
  bool valid =
      std::end(seed) == std::adjacent_find(std::begin(seed), std::end(seed));
  valid = valid && seed.size() > 15;
  // assuming that the seed is sorted
  if (seed.at(0) < 0)
    valid = false;
  return valid;
}

int tree_load_data(std::vector<int> &balanced, std::vector<int> &unbalanced) {
  std::vector<int> seed = fread();
  std::sort(std::begin(seed), std::end(seed));

  if (!tree_is_valid(seed))
    return 1;

  int index = seed.size() - 15;

  balanced = std::vector<int>(std::begin(seed) + index, std::end(seed));
  unbalanced = std::vector<int>(std::begin(seed), std::begin(seed) + index);

  return 0;
}

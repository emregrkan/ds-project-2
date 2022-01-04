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
Node *generate_tree(std::vector<int> &, int, int);
void delete_tree(Node *);
void add_new(Node *, std::vector<int> &);
void print_infix(Node *);
void print(Node *, void (*)(Node *));
int get_dl(Node *);
int nodes_at_level(Node *, int, int);
std::vector<int> fread();
bool is_valid(std::vector<int> &);
int load_data(std::vector<int> &, std::vector<int> &);

int main() {
  // void (*infix)(Node *) = print_infix;
  bool run = true;
  std::vector<int> balanced, unbalanced;
  if (load_data(balanced, unbalanced) == 1)
    return 1;
  Node *root = generate_tree(balanced, 0, balanced.size() - 1);
  add_new(root, unbalanced);

  int depth_level = get_dl(root);

  while (run) {
    std::cout << "Depth level of BST is " << get_dl(root) << std::endl;

    for (int i = 0; i < depth_level; i++)
      std::cout << "Depth level " << i + 1 << " -> "
                << nodes_at_level(root, 0, i) << std::endl;

    run = false;
  }

  delete_tree(root);
  return 0;
}

Node *generate_tree(std::vector<int> &balanced, int begin, int end) {
  if (end < begin)
    return nullptr;

  int sum = begin + end;
  int middle = (sum + (sum % 2 != 0)) / 2;
  Node *root = new Node(balanced.at(middle--));
  root->left = generate_tree(balanced, begin, middle++);
  root->right = generate_tree(balanced, ++middle, end);
  return root;
}

void delete_tree(Node *root) {
  if (root == nullptr)
    return;

  delete_tree(root->left);
  delete_tree(root->right);
  delete root;
  return;
}

void add_new(Node *root, std::vector<int> &unbalanced) {
  // needs more testing and optimization
  if (root == nullptr)
    return;

  Node *temp = root;

  for (; temp->left->left != nullptr; temp = temp->left)
    ;

  unbalanced.push_back(temp->left->data);
  std::sort(std::begin(unbalanced), std::end(unbalanced));
  delete_tree(temp->left);
  temp->left = generate_tree(unbalanced, 0, unbalanced.size() - 1);

  return;
}

void print_infix(Node *root) {
  if (root == nullptr)
    return;

  print_infix(root->left);
  std::cout << root->data << " ";
  print_infix(root->right);
  return;
}

void print(Node *root, void (*function)(Node *)) {
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

int get_dl(Node *root) {
  if (root == nullptr)
    return 0;

  int left = get_dl(root->left);
  int right = get_dl(root->right);

  return right < left ? left + 1 : right + 1;
}

int nodes_at_level(Node *root, int level, int target) {
  if (root == nullptr)
    return 0;

  if (level == target)
    return 1;

  return nodes_at_level(root->left, level + 1, target) +
         nodes_at_level(root->right, level + 1, target);
}

bool is_valid(std::vector<int> &seed) {
  bool valid =
      std::end(seed) == std::adjacent_find(std::begin(seed), std::end(seed));
  valid = valid && seed.size() > 15;
  // assuming that the seed is sorted
  if (seed.at(0) < 0)
    valid = false;
  return valid;
}

int load_data(std::vector<int> &balanced, std::vector<int> &unbalanced) {
  std::vector<int> seed = fread();
  std::sort(std::begin(seed), std::end(seed));

  if (!is_valid(seed))
    return 1;

  int index = seed.size() - 15;

  balanced = std::vector<int>(std::begin(seed) + index, std::end(seed));
  unbalanced = std::vector<int>(std::begin(seed), std::begin(seed) + index);

  return 0;
}

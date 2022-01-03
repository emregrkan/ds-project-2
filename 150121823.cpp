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
void print_infix(Node *);
void delete_tree(Node *);
std::vector<int> fread();
bool is_valid(std::vector<int> &);
int load_data(std::vector<int> &, std::vector<int> &);

int main() {
  std::vector<int> balanced, unbalanced;
  if (load_data(balanced, unbalanced) == 1)
    return 1;
  Node *root = generate_tree(balanced, 0, balanced.size() - 1);
  print_infix(root);
  delete_tree(root);
  return 0;
}

Node *generate_tree(std::vector<int> &balanced, int begin, int end) {
  if (end < begin)
    return nullptr;

  int sum = begin + end;
  int middle = (sum + (sum % 2 == 0)) / 2;
  Node *root = new Node(balanced.at(middle--));
  root->left = generate_tree(balanced, begin, middle++);
  root->right = generate_tree(balanced, ++middle, end);
  return root;
}

void print_infix(Node *root) {
  if (root == nullptr)
    return;

  print_infix(root->left);
  std::cout << root->data << " ";
  print_infix(root->right);
  return;
}

void delete_tree(Node *root) {
  if (root == nullptr)
    return;

  delete_tree(root->left);
  delete_tree(root->right);
  delete root;
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

  balanced = std::vector<int>(std::begin(seed), std::begin(seed) + 15);
  unbalanced = std::vector<int>(std::begin(seed) + 15, std::end(seed));

  return 0;
}

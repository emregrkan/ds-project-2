#include <algorithm>
#include <fstream>
#include <iomanip>
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
void fread(std::vector<int> &);

int main() {
  std::vector<int> seed;
  fread(seed);
  std::sort(std::begin(seed), std::end(seed));
  Node *root = generate_tree(seed, 0, seed.size() - 1);
  print_infix(root);
  delete_tree(root);
  return 0;
}

Node *generate_tree(std::vector<int> &seed, int begin, int end) {
  if (end < begin)
    return nullptr;

  int sum = begin + end;
  int middle = (sum + (sum % 2 == 0)) / 2;
  Node *root = new Node(seed.at(middle--));
  root->left = generate_tree(seed, begin, middle++);
  root->right = generate_tree(seed, ++middle, end);
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

void fread(std::vector<int> &seed) {
  std::ifstream fin("input.txt");
  std::istream_iterator<int> in(fin);
  std::copy(in, std::istream_iterator<int>(), std::back_inserter(seed));
  fin.close();
  return;
}

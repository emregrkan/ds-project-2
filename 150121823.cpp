#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

class Node
{
public:
    int data;
    Node* left;
    Node* right;
    Node(int);
};

Node::Node(int dataval): data(dataval), left(nullptr), right(nullptr) {}
int middle_index(int, int);
Node* generate_tree(std::vector<int>&, int, int);
void print_infix(Node*);
void delete_tree(Node*);
void fread(std::vector<int>&);

int
main()
{
    std::vector<int> seed;
    fread(seed);
    std::sort(std::begin(seed), std::end(seed));
    Node* root = generate_tree(seed, 0, seed.size() - 1);
    print_infix(root);
    delete_tree(root);
    return 0;
}

int
middle_index(int begin, int end)
{
    int mod = begin != 0 ? begin : 2;
    int sum = (end + begin) + ((end % mod) != 0);
    return sum / 2;
}

Node*
generate_tree(std::vector<int>& seed, int begin, int end)
{
    if (end < begin)
        return nullptr;

    int middle = middle_index(begin, end);
    Node* root = new Node(seed.at(middle--));
    root->left = generate_tree(seed, begin, middle++);
    root->right = generate_tree(seed, ++middle, end);
    return root;
}

void
print_infix(Node* root)
{
    if (root == nullptr)
        return;

    print_infix(root->left);
    std::cout << root->data << " ";
    print_infix(root->right);
    return;
}

void
delete_tree(Node* root)
{
    if (root == nullptr)
        return;

    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
    return;
}

void
fread(std::vector<int>& seed)
{
    std::ifstream fin("input.txt");
    std::istream_iterator<int> in(fin);
    std::copy(in, std::istream_iterator<int>(), std::back_inserter(seed));
    fin.close();
    return;
}

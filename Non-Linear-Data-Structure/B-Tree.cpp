#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
};

class BTree {
  private:
    Node *root;

    size_t tree_weight(Node *tree) {
        size_t weight = 1;
        Node *right = tree->right;
        Node *left = tree->left;
        if (right != nullptr)
            weight += tree_weight(right);
        if (left != nullptr)
            weight += tree_weight(left);
        return weight;
    }

    void delete_tree(Node *node) {
        if (node == nullptr) {
            return;
        }
        if (node->left != nullptr)
            delete_tree(node->left);
        if (node->right != nullptr)
            delete_tree(node->right);
        delete node;
    }

  public:
    BTree(int val) {
        root = new Node;
        root->data = val;
        root->right = nullptr;
        root->left = nullptr;
    }

    ~BTree() {
        delete_tree(root);
        root = nullptr;
    }

    void create_node(int val) {
        Node *new_node = new Node;
        new_node->data = val;
        new_node->left = nullptr;
        new_node->right = nullptr;
    }

    void insert(int val) {
        if (tree_weight(root->right) == tree_weight(root->left)) {
        }
    }
};

int main() {
    BTree t(7);
    return 0;
}

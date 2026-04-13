#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
  private:
    Node *root;

    Node *insert(Node *node, int val) {
        if (node == nullptr)
            return new Node(val);

        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);

        return node;
    }

    Node *deleteNode(Node *node, int key) {
        if (node == nullptr)
            return nullptr;

        if (key < node->data) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->data) {
            node->right = deleteNode(node->right, key);
        } else {

            if (node->left == nullptr) {
                Node *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    Node *findMin(Node *node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    void preorder(Node *node) {
        if (!node)
            return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node *node) {
        if (!node)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(Node *node) {
        if (!node)
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void clear(Node *node) {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

  public:
    BST() : root(nullptr) {}

    ~BST() { clear(root); }

    void insert(int val) { root = insert(root, val); }

    void remove(int val) { root = deleteNode(root, val); }

    void showPreorder() { preorder(root); }
    void showInorder() { inorder(root); }
    void showPostorder() { postorder(root); }
};

int main() {
    BST tree;

    int values[] = {42, 24, 99, 15, 50, 120, 64};
    for (int x : values) {
        tree.insert(x);
    }

    cout << "Pre-order Traversal: ";
    tree.showPreorder();
    cout << endl;

    cout << "In-order Traversal: ";
    tree.showInorder();
    cout << endl;

    cout << "Post-order Traversal: ";
    tree.showPostorder();
    cout << endl;

    tree.remove(42);

    cout << "Pre-order Traversal: ";
    tree.showPreorder();
    cout << endl;

    cout << "In-order Traversal: ";
    tree.showInorder();
    cout << endl;

    cout << "Post-order Traversal: ";
    tree.showPostorder();
    cout << endl;

    return 0;
}

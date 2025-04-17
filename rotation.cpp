#include <iostream>
using namespace std;

struct Treenode {
    int data;
    Treenode* left;
    Treenode* right;

    Treenode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Insert function for testing (basic BST insert)
Treenode* insert(Treenode* root, int val) {
    if (!root) return new Treenode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Left rotation
int leftrotation(int node, Treenode*& Tree) {
    if (!Tree || !Tree->right) return node;

    Treenode* newRoot = Tree->right;
    Tree->right = newRoot->left;
    newRoot->left = Tree;
    Tree = newRoot;

    return Tree->data;
}

// Right rotation
int Rightrotation(int node, Treenode*& Tree) {
    if (!Tree || !Tree->left) return node;

    Treenode* newRoot = Tree->left;
    Tree->left = newRoot->right;
    newRoot->right = Tree;
    Tree = newRoot;

    return Tree->data;
}

// In-order traversal to show tree structure
void inorder(Treenode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Clean up memory
void deleteTree(Treenode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Treenode* root = nullptr;

    // Sample insertions (unbalanced for demo)
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 2);

    cout << "Before Right Rotation (In-order): ";
    inorder(root);
    cout << endl;

    Rightrotation(10, root); // Perform right rotation on root

    cout << "After Right Rotation (In-order): ";
    inorder(root);
    cout << endl;

    // Adding to make left rotation visible
    root = insert(root, 8);
    root = insert(root, 9);

    cout << "Before Left Rotation (In-order): ";
    inorder(root);
    cout << endl;

    leftrotation(5, root->right); // Rotate right child of root

    cout << "After Left Rotation (In-order): ";
    inorder(root);
    cout << endl;

    deleteTree(root);
    return 0;
}
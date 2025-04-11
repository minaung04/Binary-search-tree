#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Insert function
Node* InsertBST(int x, Node* T) {
    if (T == nullptr) {
        Node* newNode = new Node();
        newNode->data = x;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (x < T->data) {
        T->left = InsertBST(x, T->left);
    } else if (x > T->data) {
        T->right = InsertBST(x, T->right);
    }
    return T; // do nothing if x already exists
}

// Helper function to find minimum value node in right subtree
Node* FindMin(Node* T) {
    while (T->left != nullptr) {
        T = T->left;
    }
    return T;
}

// Delete function
Node* DeleteBST(int x, Node* T) {
    if (T == nullptr) return nullptr;

    if (x < T->data) {
        T->left = DeleteBST(x, T->left);
    } else if (x > T->data) {
        T->right = DeleteBST(x, T->right);
    } else {
        // Node found
        if (T->left == nullptr && T->right == nullptr) {
            delete T;
            return nullptr;
        } else if (T->left == nullptr) {
            Node* temp = T->right;
            delete T;
            return temp;
        } else if (T->right == nullptr) {
            Node* temp = T->left;
            delete T;
            return temp;
        } else {
            Node* minNode = FindMin(T->right);
            T->data = minNode->data;
            T->right = DeleteBST(minNode->data, T->right);
        }
    }
    return T;
}

// In-order traversal (to check if BST is valid)
void InOrder(Node* T) {
    if (T != nullptr) {
        InOrder(T->left);
        cout << T->data << " ";
        InOrder(T->right);
    }
}

// Main function for testing
int main() {
    Node* root = nullptr;

    // Insert values
    root = InsertBST(50, root);
    root = InsertBST(30, root);
    root = InsertBST(70, root);
    root = InsertBST(20, root);
    root = InsertBST(40, root);
    root = InsertBST(60, root);
    root = InsertBST(80, root);

    cout << "BST In-Order before deletion: ";
    InOrder(root);
    cout << endl;

    // Delete values
    root = DeleteBST(30, root); // Delete node with one child
    root = DeleteBST(50, root); // Delete node with two children

    cout << "BST In-Order after deletion: ";
    InOrder(root);
    cout << endl;

    return 0;
}

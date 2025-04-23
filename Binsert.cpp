#include <iostream>
using namespace std;

const int t = 2; // Minimum degree

class BTreeNode {
public:
    int keys[2 * t - 1];
    BTreeNode* children[2 * t];
    int numKeys;
    bool isLeaf;

    BTreeNode(bool leaf) {
        isLeaf = leaf;
        numKeys = 0;
        for (int i = 0; i < 2 * t; i++)
            children[i] = nullptr;
    }

    void insertNonFull(int key) {
        int i = numKeys - 1;
        if (isLeaf) {
            while (i >= 0 && keys[i] > key) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
            numKeys++;
        } else {
            while (i >= 0 && keys[i] > key)
                i--;
            i++;
            if (children[i]->numKeys == 2 * t - 1) {
                splitChild(i, children[i]);
                if (keys[i] < key)
                    i++;
            }
            children[i]->insertNonFull(key);
        }
    }

    void splitChild(int i, BTreeNode* y) {
        BTreeNode* z = new BTreeNode(y->isLeaf);
        z->numKeys = t - 1;

        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];

        if (!y->isLeaf) {
            for (int j = 0; j < t; j++)
                z->children[j] = y->children[j + t];
        }

        y->numKeys = t - 1;

        for (int j = numKeys; j >= i + 1; j--)
            children[j + 1] = children[j];
        children[i + 1] = z;

        for (int j = numKeys - 1; j >= i; j--)
            keys[j + 1] = keys[j];
        keys[i] = y->keys[t - 1];
        numKeys++;
    }
};

class BTree {
public:
    BTreeNode* root;

    BTree() {
        root = new BTreeNode(true);
    }

    void insert(int key) {
        if (root->numKeys == 2 * t - 1) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children[0] = root;
            newRoot->splitChild(0, root);
            root = newRoot;
        }
        root->insertNonFull(key);
    }

    void printTree(BTreeNode* node, int level = 0) {
        if (node) {
            int i;
            for (i = 0; i < node->numKeys; i++) {
                if (!node->isLeaf)
                    printTree(node->children[i], level + 1);
                for (int j = 0; j < level; j++) cout << "    ";
                cout << node->keys[i] << endl;
            }
            if (!node->isLeaf)
                printTree(node->children[i], level + 1);
        }
    }

    void display() {
        printTree(root);
    }
};

int main() {
    BTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    cout << "B-Tree contents:\n";
    tree.display();

    return 0;
}

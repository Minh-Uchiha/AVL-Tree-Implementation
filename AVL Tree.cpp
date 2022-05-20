#include <bits/stdc++.h>

using namespace std;

class AVLTree {

    private:
        // Store the total number of nodes in the tree
        int nodeCnt = 0;

    public:

        // Define the structure Node with attributes: data, bf (balance factor), height, and pointers to the left and right node
        struct Node {
            int data, bf, height;
            Node* left, *right;

            // Method to create a node given an integer x
        };

        Node* createNode(int x) {

            Node* temp = (Node*)malloc(sizeof(Node));
            temp->left = temp->right = NULL;
            temp->data = x;
            temp->bf = temp->height = 0;
            return temp;

        }

        // The root node
        Node* root{NULL};

        // Constructor for AVL Tree
        AVLTree(int x) {
            root = createNode(x);
            nodeCnt = 1;
        }

        // An empty contructor
        AVLTree() {

        }

        // Method to get the size of tree
        int getSize() {
            return this->nodeCnt;
        }

        //Method to get height
        int getHeight() {
            return root->height;
        }

        // Method to display the tree with parameter root. This will be the helper function for the display method below
        void display(Node* root) {
            if (root == NULL) return;
            display(root->left);
            cout << root->data << " ";
            display(root->right);
        }

        // Method to display the tree
        void display() {
            display(root);
        }

        // Method to check if the tree contains a value. This will be the helper function for the contains method below
        bool contains(Node* root, int x) {

            if (root == NULL) return false;
            if (root->data == x) return true;
            return (contains(root->left, x) || contains(root->right, x));

        }

        // Method to check if the tree contains a value
        bool contains(int x) {
            return contains(root, x);
        }

        // Check if the tree is empty
        bool isEmpty() {
            return (this->getSize() == 0);
        }

        // Function to update the balance factor and height of tree
        void update(Node* root) {

            if (root == NULL) return;
            int leftSubTreeHeight = (root->left == NULL ? -1 : root->left->height);
            int rightSubTreeHeight = (root->right == NULL ? -1 : root->right->height);

            root->height = 1 + max(leftSubTreeHeight, rightSubTreeHeight);
            root->bf = leftSubTreeHeight - rightSubTreeHeight;

        }

        Node* leftRotation(Node* root) {
            Node* newParent = root->right;
            root->right = newParent->left;
            newParent->left = root;
            update(root);
            update(newParent);
            return newParent;
        }

        Node* rightRotation(Node* root) {
            Node* newParent = root->left;
            root->left = newParent->right;
            newParent->right = root;
            update(root);
            update(newParent);
            return newParent;
        }

        Node* leftLeftCase(Node* root) {
            root = rightRotation(root);
        }

        Node* leftRightCase(Node* root) {
            root->left = leftRotation(root->left);
            root = rightRotation(root);
        }

        Node* rightRightCase(Node* root) {
            root = leftRotation(root);
        }

        Node* rightLeftCase(Node* root) {
            root->right = rightRotation(root->right);
            root = leftRotation(root);
        }

        Node* balance(Node* root) {

            if (root->bf == -2) {
                if (root->right->bf <= 0) root = rightRightCase(root);
                else root = rightLeftCase(root);
            } else if (root->bf == 2) {
                if (root->left->bf >= 0) root = leftLeftCase(root);
                else root = leftRightCase(root);
            }
            return root;

        }

        // Helper function to insert a Node
        Node* insertNode(Node* root, int x) {
            if (root == NULL) return createNode(x);
            if (root->data > x) root->left = insertNode(root->left, x);
            else root->right = insertNode(root->right, x);

            update(root);
            return balance(root);

        }

        // Method to insert a node into the tree
        bool insertNode(int x) {
            if (!this->contains(x)) {
                ++ this->nodeCnt;
                root = insertNode(root, x);
                return true;
            }
            return false;
        }


};


int main() {

    ios_base::sync_with_stdio(0);
    AVLTree tree;
    srand(time(0));
    int n;
    cin >> n;
    while (n --) {
        tree.insertNode(rand()%100 + 1);
    }
    tree.display();
    cout << "\n" << tree.getHeight();
    return 0;

}

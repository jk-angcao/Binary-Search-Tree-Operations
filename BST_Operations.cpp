#include <iostream>

using namespace std;

class Node {
    public:
    int val;
    Node* left;
    Node* right;

    Node(int value, Node* left_child = NULL, Node* right_child = NULL) {
        val = value;
        left = left_child;
        right = right_child;
    }
};


class BST {
    public:
    Node* root = nullptr;

    void insert(int val) {
        //If there's no root node, we create one
        if (root == nullptr) {
            root = new Node(val);
            return;
        }
        
        //If there is a root, check its children
        Node* curr = root;
        while(curr != nullptr) {
            //If our value is less than the current node, check the left child
            if ((val < curr->val) && (curr->left != nullptr)) {
                curr = curr->left;
            }
            //If our value is greater than the current node, check the right child
            else if ((val > curr->val) && (curr->right != nullptr)) {
                curr = curr->right;
            }
            //If there are no children, exit the loop
            else {
                break;
            }
        }
        //If our value is less than the current node, make the value its left child
        if (val < curr->val) {
            curr->left = new Node(val);
        }
        //If our value is greater than or equal to the current node, make it the right child
        else {
            curr->right = new Node(val);
        }

        return;
    }

    bool search(int val) {
        Node* curr = root;

        while (curr) {
            //If our value is less than the current node, check the left child
            if (val < curr->val) {
                curr = curr->left;
            }
            //If our value is greater than the current node, check the right child
            else if (val > curr->val) {
                curr = curr->right;
            }
            //If the current node still exists at this point, then this must be the value
            else {
                return true;
            }
        }
        //We have landed on a null pointer; the value is not in the tree
        return false;
    }

    void remove(int val) {
        Node* parent = nullptr;
        Node* curr = root;
        while (curr) {
            //If our value is less than the current node, check the left child
            if (val < curr->val) {
                parent = curr;
                curr = curr->left;
            }
            //If our value is greater than the current node, check the right child
            else if (val > curr->val) {
                parent = curr;
                curr = curr->right;
            }
            //If the current node still exists at this point, then this must be the value
            else {
                break;
            }
        }
        //If we started on or landed on a null pointer, the value did not exist in the tree
        if (curr == nullptr) {
            return;
        }
        //If there are two children, traverse to the right child's leftmost successor
        if (curr->left && curr->right) {
            Node* successor = curr->right;
            while (successor->left) {
                successor = successor->left;
            }
            //Make the successor steal the other node's left child
            successor->left = curr->left;
            curr->left = nullptr;
        }

        //Start process to move its descendants up
        Node* new_child;
        if (curr->left) {
            new_child = curr->left;
        }
        else {
            new_child = curr->right;
        }

        //If the node has no parent, then it is the root. Replace the root
        if (parent == nullptr) {
            root = new_child;
        }
        //Have parent node point to the current node's "dominant" child
        else if (parent->left == curr) {
            parent->left = new_child;
        }
        else {
            parent->right = new_child;
        }

        //FINALLY WE DELETE THE NODE
        delete curr;
        return;
    }

    //The actual traverser
    void inOrderHelper(Node* curr) {
        //Go through left subtree
        if (curr->left) {    
            inOrderHelper(curr->left);
        }
        
        //Return current value
        cout << curr->val << ", ";
        
        //Go through right subtree
        if (curr->right) {
        inOrderHelper(curr->right);
        }
    } 

    //The functions can't automatically call the root, so that's why there are so many helpers
    void inOrderTraversal() {
        inOrderHelper(root);
        return;
    }

    void preOrderHelper(Node* curr) {
        cout << curr->val << ", ";
        if (curr->left) {
            preOrderHelper(curr->left);
        }
        if (curr->right) {
            preOrderHelper(curr->right);
        }
    }

    void preOrderTraversal() {
        preOrderHelper(root);
        return;
    }

    void postOrderHelper(Node* curr) {
        if (curr->left) {
            postOrderHelper(curr->left);
        }
        if (curr->right) {
            postOrderHelper(curr->right);
        }
        cout << curr->val << ", ";
        return;
    }

    void postOrderTraversal() {
        postOrderHelper(root);
        return;
    }

    int heightHelper(Node* curr) {
        if (curr == nullptr) {
            return -1;
        }
        return (1 + max(heightHelper(curr->left), heightHelper(curr->right)));
    }

    int height() {
        return heightHelper(root);
    }
};

int main() {
    cout << boolalpha;
    BST tree;

    int DA_LIST[] = {3, 2, 7, 6, 1, 12, 5, 10, 13, 11, 14, 9, 4, 8};
    for (int i : DA_LIST) {
        tree.insert(i);
    }

    cout << "Inorder Traversal: ";
    tree.inOrderTraversal();
    cout << endl;

    cout << "PreOrder Traversal: ";
    tree.preOrderTraversal();
    cout << endl;

    cout << "PostOrder Traversal: ";
    tree.postOrderTraversal();
    cout << endl << endl;

    cout << "Deleting present key, [5]\n";
    tree.remove(5);
    cout << "New order: ";
    tree.inOrderTraversal();
    cout << endl;
    cout << "Deleting key not present, [15]\n";
    tree.remove(11);
    cout << "New order: ";
    tree.inOrderTraversal();
    cout << endl << endl;

    cout << "Deleting node with no children, [4]" << endl;
    tree.remove(4);
    cout << "   New order: ";
    tree.inOrderTraversal();
    cout << endl;
    cout << "Deleting node with one child, [9]" << endl;
    tree.remove(9);
    cout << "   New order: ";
    tree.inOrderTraversal();
    cout << endl;
    cout << "Deleting node with two children, [9]" << endl;
    tree.remove(7);
    cout << "   New order: ";
    tree.inOrderTraversal();
    cout << endl;
}

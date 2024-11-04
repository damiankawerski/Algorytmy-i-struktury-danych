#include <iostream>

struct node {
    int data;
    node* left;
    node *right;

    node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class TreeBST {
public:
    node *root;

    TreeBST() {
        root = nullptr;
    }

    node* insert(node *inserted_node, int data) {
        if(inserted_node == nullptr) {
            return new node(data);
        }

        if(data < inserted_node->data) {
            inserted_node->left = insert(inserted_node->left, data);
        } else {
            inserted_node->right = insert(inserted_node->right, data);
        }

        return inserted_node;
    }


};
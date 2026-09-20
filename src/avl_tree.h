#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data): val(data), height(0), left(nullptr), right(nullptr) {}

    TreeNode* insert(TreeNode* root, int key) {
        /**
        // first you do the base case which is checking if node is nullptr bcs if it has nothing then thats the value
        if (root == nullptr) return new TreeNode(key);

        // then you want to check
        else if (key < root->val) { // means it should go on the left
            root->left = insert(root->left, key);
        }
        else {

        }
        */




        return root;
    }
};


class AVLTree {
    public:
    bool insert(const string& name, const string& id) { return false; }
    bool remove(const string& id) { return false; }
    vector<string> inorder() { return {}; }
    vector<string> preorder() { return{}; }
};


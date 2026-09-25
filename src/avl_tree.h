#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

/** 
 * Notes to self:
 * Binary Search Tree
 * 2-ary tree (every node has atmost 2 children)
 * is a type of B Tree
 * 
 * Balanced Tree (AVL)
 * avoids spindly tree case
 * ensures it can have O(logn) time complexity for remove, insert, search functions
*/

#include <iostream>
#include <vector>
struct TreeNode {
    int val;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data): val(data), left(nullptr), right(nullptr) {}
};

class AVLTree {
    public:
    bool insert(const string& name, const string& id) { return false; }
    bool remove(const string& id) { return false; }
    vector<string> inorder() { return {}; }
    vector<string> preorder() { return {}; }
    vector<string> postorder() { return {}; }
    TreeNode* rotateRight(TreeNode* y);
    TreeNode* rotateLeft(TreeNode* y);
};

// helper functions
int height (TreeNode* root) {
    if (root == nullptr) return 0;
    return root->height;
}

int balanceFactor(TreeNode* root) {
    if (root == nullptr) return 0;
    return height(root->left) - height(root->right);
}

void updateHeight(TreeNode* root) {
    root->height = 1 + max(height(root->left), height(root->right));
}




/**
 * 
 * rotate right would mean that the children are skewed to the left so u rotate y to the right 
 *          y                     x = y->left
 *         /                     / \
 *        x         ->          0   y xr = x->right
 *       /                
 *      0
 */
TreeNode* rotateRight(TreeNode* y) {
    TreeNode* x = y->left; // x is the left child of y
    TreeNode* xr = x->right; // xr is right child of x in which x is the left child of y

    x->right = y; 
    y->left = xr;

    updateHeight(y);
    updateHeight(x);

    return x;
}




TreeNode* rotateLeft(TreeNode* y) {
    // have x be y's right child
    // have xl be x's left child
    TreeNode* x = y->right;
    TreeNode* xl = x->left;

    x->left = y;
    y->right = xl;

    updateHeight(y);
    updateHeight(x);

    return x;
}

TreeNode* rotateLeftRight(TreeNode* y) {
    if (balance > 1 )
}


 // the three different cases
// if it is an empty tree
// if its not, see if the value we are inserting is less than or greater than the root
// then if it is, we use a recursive call on our insert function in order to get the node with that respective key assigned to its proper placement within the BST
TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr) return new TreeNode(key); // if root == nullptr then return new node!!!
    else if (key < root->val) {
        root->left = insert(root->left, key);
    }
    else {
        root->right = insert(root->right, key);
    }
    return root;
}

TreeNode* remove(TreeNode* root, int key) {
    if (root == nullptr) return nullptr;

    if (key < root->val ) root->left = remove(root->left, key);

    else if (key > root->val ) root->right = remove(root->right, key);

    // is when key == root->val whichis where we want to be in order to see what to do when removing
    else {
        // if the node we want to remove has only a left child
        // if the node we want to remove has only right child
        // two children if the node we want to remove has both a left and right child
        // if it has two children we what we will want to do is replace the value with its sucessor and then delete the root and return child and then delete the child since we now have two nodes with the same value and we do not want to have stray duplicates in our BST
    
        if (root->left == nullptr)  {
            TreeNode* child = root->right;
            delete root;
            return child;
        }
        else if (root->right == nullptr) {
            TreeNode* child = root->left; // save the value of the child
            delete root;
            return child;
        }
        else {
            // has successor
            TreeNode* succ = root->right; // start with the right subtree 
            // go all the way left until it is null
            while(succ->left != nullptr) succ = succ->left;
            root->val = succ->val;
            root->right = remove(root->right, root->val);
        }
    }
    return root;
}

// NLR
void preorder(TreeNode* root) {
    if (!root) return;
    std::cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->val << " ";
    inorder(root->right);
}

void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left); // prints al the contents in the left subtree
    postorder(root->right); // prints all the contents in the right subttree
    std::cout << root->val << " ";
}

int main() {
    TreeNode* root = nullptr;

    for(int k : {50,30,70,40,80,60,90}) {
        root = insert(root, k);
    }

    inorder(root);
    std::cout << "remove 70" << std::endl;
    remove(root, 70);
    std::cout << "after removal" << std::endl;
    inorder(root);

    return 0;
}

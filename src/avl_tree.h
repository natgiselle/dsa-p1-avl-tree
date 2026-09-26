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

struct TreeNode {
    string name;
    int id; // instead of val(data) use id as the actual data and name for string data as well
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string name_, int id_): name(name_), id(id_), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
    public:
        // helpers for the public declaration of the function logic I already made
        bool insert(const string& name, const string& strId);
        bool remove(const string& strId);
        vector<string> searchByName(const string& name);
        string searchById(const string& strId);
        bool removeInorder(int nodes);
        int printLevel();

        vector<string> inorder();
        vector<string> preorder();
        vector<string> postorder();
        
        ~AVLTree();

    private: 
        TreeNode* root = nullptr;
        // validation for name and ID
        bool idIsValid(const string& id);
        bool nameIsValid(const string& name);
        // helper functions
        int height(TreeNode* root);
        int balanceFactor(TreeNode* root);
        void updateHeight(TreeNode* root);
        int levelCount(TreeNode* root);
        // tree detructor deleting left subtree first, then right subtree, and lastly deleting the root so that we can still access its children before deleting root itself which is why root is deleted last!
        void treeDestructor(TreeNode* root);
        TreeNode* searchByIdHelper(TreeNode* root, int id);
        void searchByNameHelper(TreeNode* root, const string& name, vector<int>& searchMatches);
        bool findNthOrder(TreeNode* root, int& nodes, int& foundId);
        TreeNode* rotateRight(TreeNode* y);
        TreeNode* rotateLeft(TreeNode* y);
        TreeNode* rotateLeftRight(TreeNode* root);
        TreeNode* rotateRightLeft(TreeNode* root);
        TreeNode* updateBalanceFactor(TreeNode* root);
        TreeNode* insertHelper(TreeNode* root, const string& name, int id, bool& success);
        TreeNode* removeHelper(TreeNode* root, int id, bool& success);
        // order traversals
        void preorderHelper(TreeNode* root, vector<string>& out);
        void inorderHelper(TreeNode* root, vector<string>& out);
        void postorderHelper(TreeNode* root, vector<string>& out);
};
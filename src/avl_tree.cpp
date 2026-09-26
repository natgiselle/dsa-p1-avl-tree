#include "avl_tree.h"

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


bool AVLTree::insert(const string& name, const string& strId) {
    if (!nameIsValid(name) || !idIsValid(strId)) return false;
    int id = stoi(strId);
    bool success = false;
    root = insertHelper(root, name, id, success);
    return success;
}

bool AVLTree::remove(const string& strId) {
    if (!idIsValid(strId)) return false;
    int id = stoi(strId);
    bool success = false;
    root = removeHelper(root, id, success);
    return success;
}

vector<string> AVLTree::searchByName(const string& name) {
    vector<string> results;
    if (!nameIsValid(name)) {
        results.push_back("unsuccessful");
        return results;
    }
    vector<int> search_matches;
    searchByNameHelper(root, name, search_matches);
    if (search_matches.empty()) {
        results.push_back("unsuccessful");
        return results;
    }
    for (int id : search_matches) {
        string IDstr = to_string(id);
        while (IDstr.size() < 8) IDstr = "0" + IDstr;
        results.push_back(IDstr);
    }
    return results;
}

string AVLTree::searchById(const string& strId) {
    if (!idIsValid(strId)) return "unsuccessful";
    TreeNode* found = searchByIdHelper(root, stoi(strId));
    if (found) return found->name;
    else {
        return "unsuccessful";
    }
}

bool AVLTree::removeInorder(int nodes) {
    int foundId;
    if (!findNthOrder(root, nodes, foundId)) return false;
    bool success = false;
    root = removeHelper(root, foundId, success);
    return success;
}

int AVLTree::printLevel() {
    return height(root);
}

vector<string> AVLTree::inorder() {
    vector<string> out;
    inorderHelper(root, out);
    return out;
}

vector<string> AVLTree::preorder() {
    vector<string> out;
    preorderHelper(root, out);
    return out;
}

vector<string> AVLTree::postorder() {
    vector<string> out;
    postorderHelper(root, out);
    return out;
}

AVLTree::~AVLTree() {
    treeDestructor(root);
}

// validation for name and ID
bool AVLTree::idIsValid(const string& id) {
    // ^ means must start with any digit from 0-9 and be repeated 8 times 
    // and $ ends
    static const regex idPattern("^[0-9]{8}$");
    return regex_search(id, idPattern);
}

bool AVLTree::nameIsValid(const string& name) {
    // matches exact characters to ensure the User doesnt input numbers or special characters 
    // regex is cool! I find it much better than a traditional manner of doing it like a bunch of if statements
    static const regex namePattern("^[A-Za-z\\s]+$"); // static const to make sure it doesnt have to rebuild each time
    return regex_search(name, namePattern);
}

// helper functions
int AVLTree::height(TreeNode* root) {
    if (root == nullptr) return 0;
    return root->height;
}

int AVLTree::balanceFactor(TreeNode* root) {
    if (root == nullptr) return 0;
    return height(root->left) - height(root->right);
}

void AVLTree::updateHeight(TreeNode* root) {
    root->height = 1 + max(height(root->left), height(root->right));
}

// tree detructor deleting left subtree first, then right subtree, and lastly deleting the root so that we can still access its children before deleting root itself which is why root is deleted last!
void AVLTree::treeDestructor(TreeNode* root) {
    if(root == nullptr) return;
    treeDestructor(root->left);
    treeDestructor(root->right);
    delete root; 
}


TreeNode* AVLTree::searchByIdHelper(TreeNode* root, int id) {
    if (root == nullptr || root->id == id) return root;
    if (id < root->id) return searchByIdHelper(root->left, id); // recursively call in order to search for the right node that has these attirbutes for name and id
    return searchByIdHelper(root->right, id);
}

void AVLTree::searchByNameHelper(TreeNode* root, const string& name, vector<int>& searchMatches ) {
    // visits root, then goes left or right to find the name
    if (root == nullptr) return; 
    if (root->name == name) searchMatches.push_back(root->id);
    searchByNameHelper(root->left, name, searchMatches); 
    searchByNameHelper(root->right, name, searchMatches);
}

bool AVLTree::findNthOrder(TreeNode* root, int& nodes, int& foundId) {
    if (root == nullptr) return false;
    if (findNthOrder(root->left, nodes, foundId)) return true;
    if (nodes == 0) {
        foundId = root->id;
        return true;
    }
    nodes--; // continue count down
    return findNthOrder(root->right, nodes, foundId);
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
TreeNode* AVLTree::rotateRight(TreeNode* y) {
    TreeNode* x = y->left; // x is the left child of y
    TreeNode* xr = x->right; // xr is right child of x in which x is the left child of y

    x->right = y; 
    y->left = xr;

    updateHeight(y);
    updateHeight(x);

    return x;
}

TreeNode* AVLTree::rotateLeft(TreeNode* y) {
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

TreeNode* AVLTree::rotateLeftRight(TreeNode* root) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
}

TreeNode* AVLTree::rotateRightLeft(TreeNode* root) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
}

TreeNode* AVLTree::updateBalanceFactor(TreeNode* root) {
    int balance = balanceFactor(root);
    if (balance > 1 && balanceFactor(root->left) >= 0) return rotateRight(root);
    if (balance < -1 && balanceFactor(root->right) <= 0) return rotateLeft(root);
    if (balance > 1 && balanceFactor(root->left) < 0) return rotateLeftRight(root);
    if (balance < -1 && balanceFactor(root->right) > 0) return rotateRightLeft(root);
    return root;
}


// the three different cases
// if it is an empty tree
// if its not, see if the value we are inserting is less than or greater than the root
// then if it is, we use a recursive call on our insert function in order to get the node with that respective key assigned to its proper placement within the BST
TreeNode* AVLTree::insertHelper(TreeNode* root, const string& name, int id, bool& success) {
    if (root == nullptr) {
        success = true;
        return new TreeNode(name, id); // if root == nullptr then return new node!!!
    }
    if (id < root->id) {
        root->left = insertHelper(root->left, name, id, success);
    }
    else if (id > root->id) {
        root->right = insertHelper(root->right, name, id, success);
    }
    else {
        success = false;
        return root;
    }
    updateHeight(root);
    return updateBalanceFactor(root);
}

TreeNode* AVLTree::removeHelper(TreeNode* root, int id, bool& success) {
    if (root == nullptr) {
        success = false;
        return nullptr;
    }
    if (id < root->id) root->left = removeHelper(root->left, id, success);

    else if (id > root->id) root->right = removeHelper(root->right, id, success);

    // is when key == root->val which is where we want to be in order to see what to do when removing
    else {
        // if the node we want to remove has only a left child
        // if the node we want to remove has only right child
        // two children if the node we want to remove has both a left and right child
        // if it has two children we what we will want to do is replace the value with its successor and then delete the root and return child and then delete the child since we now have two nodes with the same value and we do not want to have stray duplicates in our BST
        success = true;
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
            root->id = succ->id;
            root->name = succ->name;
            bool placeholder = false; // default it to false and then it will change after going thru the recursive call
            root->right = removeHelper(root->right, root->id, placeholder);
        }
    }
    updateHeight(root);
    return root;
}

// NLR
void AVLTree::preorderHelper(TreeNode* root, vector<string>& out) {
    if (!root) return;
    out.push_back(root->name);
    preorderHelper(root->left, out);
    preorderHelper(root->right, out);
}
// LNR
void AVLTree::inorderHelper(TreeNode* root, vector<string>& out) {
    if (!root) return;
    inorderHelper(root->left, out);
    out.push_back(root->name);
    inorderHelper(root->right, out);
}
// LRN
void AVLTree::postorderHelper(TreeNode* root, vector<string>& out) {
    if (!root) return;
    postorderHelper(root->left, out); // prints all the contents in the left subtree
    postorderHelper(root->right, out); // prints all the contents in the right subttree
    out.push_back(root->name);
}

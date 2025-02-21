/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class FindElements {
TreeNode* root;
public:
    FindElements(TreeNode* root) : root(root) { // Store root pointer
        reconstruct(root, 0);  // Use helper function for cleaner code
    }

    void reconstruct(TreeNode* node, int val) {
        if (!node) return;
        node->val = val;
        reconstruct(node->left, (val << 1) + 1);
        reconstruct(node->right, (val << 1) + 2);
    }
    
    bool find(int target) {
        TreeNode* obj = root; // Start from root every time
        vector<bool> op; // 0 left, 1 right

        while (target != 0) {
            if (target % 2) { // Odd -> left
                (--target) >>= 1;
                op.push_back(false);
            } else { // Even -> right
                target = (target - 2) >> 1;
                op.push_back(true);
            }
        }

        for (int i = (int)op.size() - 1; i >= 0; i--) {
            if (op[i]) { // Go right
                if (!obj->right) return false;
                obj = obj->right;
            } else { // Go left
                if (!obj->left) return false;
                obj = obj->left;
            }
        }
        return true;
    }
};


/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
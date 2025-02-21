#include <unordered_set>

class FindElements {
    TreeNode* root;
    std::unordered_set<int> values; // Store all valid values for O(1) find()

    void reconstruct(TreeNode* node, int val) {
        if (!node) return;
        node->val = val;
        values.insert(val); // Store valid values for quick lookup
        reconstruct(node->left, (val << 1) + 1);
        reconstruct(node->right, (val << 1) + 2);
    }

public:
    FindElements(TreeNode* root) : root(root) {
        reconstruct(root, 0);
    }
    
    bool find(int target) {
        return values.count(target); // O(1) lookup
    }
};

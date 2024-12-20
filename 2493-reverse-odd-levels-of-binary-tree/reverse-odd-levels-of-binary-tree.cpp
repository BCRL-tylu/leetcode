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
class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        if (!root) return nullptr;

        std::vector<std::vector<int>> levels; // To store values of each level
        std::queue<TreeNode*> q;
        q.push(root);

        // Perform level order traversal
        while (!q.empty()) {
            int size = q.size();
            std::vector<int> currentLevel;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                currentLevel.push_back(node->val); // Store current level's values
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            levels.push_back(currentLevel);
        }

        // Reverse values at odd levels
        for (int i = 1; i < levels.size(); i += 2) {
            std::reverse(levels[i].begin(), levels[i].end());
        }

        // Reassign the values back to the tree
        q.push(root);
        int levelIndex = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                node->val = levels[levelIndex][i]; // Reassign the value from the levels vector
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            levelIndex++;
        }

        return root; // Return the modified tree
    }
};

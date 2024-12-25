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
    vector<int> largestValues(TreeNode* root) {
        if (!root) return {};
        // BFS to traverse the tree level by level
        queue<TreeNode*> q;
        q.push(root);
        vector<int> l;

        while (!q.empty()) {
            int n = q.size();
            int cl  = INT_MIN;

            // Collect all nodes at the current level
            for (int i = 0; i < n; ++i) {
                TreeNode* node = q.front();
                q.pop();
                cl = max(cl,node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            // Count minimum swaps required to sort the current level
            l.push_back(cl);
        }
        return l;
    }
};
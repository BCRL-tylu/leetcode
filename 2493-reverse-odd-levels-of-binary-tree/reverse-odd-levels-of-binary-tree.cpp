class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        std::queue<TreeNode*> q; // store even levels
        std::deque<TreeNode*> dq; // store odd levels

        q.push(root);
        // Perform level order traversal
        bool odd_line = true;
        while (!q.empty() || !dq.empty()) {
            odd_line = !odd_line; // toggle between odd and even levels
            
            if (odd_line) {
                int size = dq.size();
                std::deque<TreeNode*> temp_dq;
                for (int i = 0; i < (size + 1) / 2; ++i) {
                    // Process nodes from both ends of dq
                    TreeNode* node_back = dq.back();
                    TreeNode* node_front = dq.front();
                    dq.pop_back();
                    dq.pop_front();
                    
                    if (node_back && node_front) {
                        // Swap values between front and back nodes
                        auto back = node_back->val;
                        node_back->val = node_front->val;
                        node_front->val = back;
                        // Add valid children to the next level
                        if (node_front->left) q.push(node_front->left);
                        if (node_front->right) q.push(node_front->right);
                        if (node_back->right) temp_dq.push_front(node_back->right);
                        if (node_back->left) temp_dq.push_front(node_back->left);
                    }
                }
                while (!temp_dq.empty()) {
                    q.push(temp_dq.front());
                    temp_dq.pop_front();
                }
            } else {
                int size = q.size();
                for (int i = 0; i < size; ++i) {
                    TreeNode* node = q.front();
                    q.pop();
                    if (node->left) dq.push_back(node->left);
                    if (node->right) dq.push_back(node->right);
                }
            }
        }
        return root; // Return the modified tree
    }
};

class Solution {
public:
    int minimumOperations(TreeNode* root) {
        if (!root) return 0;

        // BFS to traverse the tree level by level
        queue<TreeNode*> q;
        q.push(root);
        int totalSwaps = 0;

        while (!q.empty()) {
            int n = q.size();
            vector<int> levelNodes;

            // Collect all nodes at the current level
            for (int i = 0; i < n; ++i) {
                TreeNode* node = q.front();
                q.pop();
                levelNodes.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            // Count minimum swaps required to sort the current level
            totalSwaps += countMinSwaps(levelNodes);
        }

        return totalSwaps;
    }

private:
    int countMinSwaps(vector<int>& arr) {
        int n = arr.size();
        vector<pair<int, int>> pairs(n);
        for (int i = 0; i < n; ++i) {
            pairs[i] = {arr[i], i};
        }

        // Sort based on the array values
        sort(pairs.begin(), pairs.end());
        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; ++i) {
            // Skip already visited or correctly placed elements
            if (visited[i] || pairs[i].second == i) continue;

            // Find the cycle length
            int cycleLength = 0, j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = pairs[j].second;
                cycleLength++;
            }

            // Add the swaps for this cycle
            if (cycleLength > 1) swaps += (cycleLength - 1);
        }

        return swaps;
    }
};

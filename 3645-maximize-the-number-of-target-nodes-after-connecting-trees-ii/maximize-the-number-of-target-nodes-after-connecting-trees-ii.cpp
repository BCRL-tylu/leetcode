class Solution {
public:
    typedef pair<int, int> pii; // Shorthand for a pair of integers
    typedef vector<int> vi;    // Shorthand for a vector of integers

    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1; // Number of nodes in tree 1
        int m = edges2.size() + 1; // Number of nodes in tree 2

        // Step 1: Build adjacency lists dynamically
        vector<vector<int>> adj1(n), adj2(m);
        for (auto& edge : edges1) {
            adj1[edge[0]].push_back(edge[1]);
            adj1[edge[1]].push_back(edge[0]);
        }
        for (auto& edge : edges2) {
            adj2[edge[0]].push_back(edge[1]);
            adj2[edge[1]].push_back(edge[0]);
        }

        // Step 2: BFS for labeling nodes in tree 1
        vi labels1(n, -1); // -1 means unvisited
        int labelCount1 = 0; // To count the total number of nodes with label 0
        queue<int> q;

        q.push(0); // Start BFS from node 0
        labels1[0] = 0; // Label root as 0
        labelCount1++;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (int neighbor : adj1[current]) {
                if (labels1[neighbor] == -1) { // If unvisited
                    labels1[neighbor] = 1 - labels1[current]; // Alternate label
                    if (labels1[neighbor] == 0) {
                        labelCount1++; // Increment count for label 0
                    }
                    q.push(neighbor);
                }
            }
        }

        // Step 3: BFS for counting labels in tree 2
        int labelCount2 = 0; // Count of nodes with label 0 in tree 2
        vector<bool> visited2(m, false); // Use vector<bool> for memory efficiency
        queue<pii> q2;

        q2.push({0, 0}); // Start BFS from node 0
        visited2[0] = true;
        labelCount2++; // Root is labeled 0

        while (!q2.empty()) {
            auto [current, label] = q2.front();
            q2.pop();
            for (int neighbor : adj2[current]) {
                if (!visited2[neighbor]) { // If unvisited
                    int newLabel = 1 - label; // Alternate label
                    if (newLabel == 0) {
                        labelCount2++; // Increment count for label 0
                    }
                    visited2[neighbor] = true;
                    q2.push({neighbor, newLabel});
                }
            }
        }

        // Step 4: Compute results
        int maxLabel2 = max(labelCount2, (m - labelCount2)); // Max count of either label
        vi result(n);

        for (int i = 0; i < n; i++) {
            result[i] = (labels1[i] == 0 ? labelCount1 : (n - labelCount1)) + maxLabel2;
        }
        return result;
    }
};

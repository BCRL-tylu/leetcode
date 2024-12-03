class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1; // Number of nodes in tree 1
        int m = edges2.size() + 1; // Number of nodes in tree 2

        // Step 1: Build adjacency lists
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
        vector<int> labels1(n, -1); // -1 means unvisited
        vector<int> labelCounts1(2, 0); // Count of nodes with labels 0 and 1
        queue<int> q;

        // Start BFS from an arbitrary root (node 0)
        q.push(0);
        labels1[0] = 0;
        labelCounts1[0]++;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (int neighbor : adj1[current]) {
                if (labels1[neighbor] == -1) { // If unvisited
                    labels1[neighbor] = 1 - labels1[current]; // Alternate label
                    labelCounts1[labels1[neighbor]]++;
                    q.push(neighbor);
                }
            }
        }

        // Step 3: BFS for counting labels in tree 2
        vector<int> labelCounts2(2, 0);
        vector<bool> visited2(m, false);
        queue<pair<int, int>> q2;

        q2.push({0, 0}); // Start BFS from an arbitrary root (node 0)
        visited2[0] = true;
        labelCounts2[0]++;

        while (!q2.empty()) {
            auto [current, label] = q2.front();
            q2.pop();
            for (int neighbor : adj2[current]) {
                if (!visited2[neighbor]) { // If unvisited
                    int newLabel = 1 - label; // Alternate label
                    labelCounts2[newLabel]++;
                    visited2[neighbor] = true;
                    q2.push({neighbor, newLabel});
                }
            }
        }

        // Step 4: Compute results
        int maxLabel2 = max(labelCounts2[0], labelCounts2[1]);
        vector<int> result(n);

        for (int i = 0; i < n; i++) {
            result[i] = labelCounts1[labels1[i]] + maxLabel2;
        }
        return result;
    }
};

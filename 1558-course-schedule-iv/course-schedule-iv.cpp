class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& pre, vector<vector<int>>& q) {
        // Build adjacency list and in-degree array
        vector<vector<int>> adj(n);
        vector<int> inDeg(n, 0);
        for (auto& p : pre) {
            adj[p[0]].push_back(p[1]);
            inDeg[p[1]]++;
        }

        // Topological Sort and Propagation using bitset
        vector<bitset<200>> prereq(n); // Store prerequisite info
        queue<int> todo;

        // Add all nodes with in-degree 0 to the queue
        for (int i = 0; i < n; ++i) {
            if (inDeg[i] == 0) todo.push(i);
        }

        while (!todo.empty()) {
            int cur = todo.front();
            todo.pop();
            for (int nxt : adj[cur]) {
                prereq[nxt] |= prereq[cur]; // Merge prerequisite info
                prereq[nxt][cur] = true;   // Add current node as prerequisite
                if (--inDeg[nxt] == 0) {
                    todo.push(nxt);
                }
            }
        }
        
        // Answer Queries
        vector<bool> ans;
        for (auto& p : q) {
            ans.push_back(prereq[p[1]][p[0]]);
        }
        return ans;
    }
};

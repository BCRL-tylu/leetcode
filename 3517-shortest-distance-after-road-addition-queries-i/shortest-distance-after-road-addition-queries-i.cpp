class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<pair<int, int>> hm(n); // [parent, distance]
        vector<unordered_set<int>> children(n); // Store children with unique relationships
        // Initialize parent and distance
        hm[0] = {n, 0};
        for (int i = 1; i < n; i++) {
            hm[i] = {i - 1, i}; // Parent and initial distance
            children[i - 1].emplace(i); // Add child relationship
        }
        vector<int> rt(queries.size());
        for (int j = 0; j < queries.size(); j++) {
            int newParent = queries[j][0];
            int node = queries[j][1];
            // Add node to the children of newParent if not already present
            if (children[newParent].find(node) == children[newParent].end()) {
                children[newParent].emplace(node);
            }
            int nps = hm[newParent].second + 1;
            if (hm[node].second > nps) {
                hm[node].first = newParent;
                hm[node].second = nps;
                // Update distances using BFS
                queue<int> q;
                q.emplace(node);
                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    int updated = hm[curr].second + 1;
                    for (int child : children[curr]) {
                        if (hm[child].second > updated) {
                            hm[child].second = updated;
                            q.emplace(child);
                        }
                    }
                }
            }
            rt[j] = hm[n - 1].second;
        }
        return rt;
    }
};

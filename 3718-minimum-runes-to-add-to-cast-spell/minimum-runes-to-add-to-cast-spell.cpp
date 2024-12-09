class Solution {
public:
    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {
        // Build adjacency list and reverse adjacency list
        vector<vector<int>> adj(n), revAdj(n);
        for (int i = 0; i < flowFrom.size(); i++) {
            adj[flowFrom[i]].push_back(flowTo[i]);
            revAdj[flowTo[i]].push_back(flowFrom[i]);
        }

        vector<bool> visited(n, false);
        stack<int> order;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, order);
            }
        }

        vector<int> sccId(n, -1);
        int sccCount = 0;
        while (!order.empty()) {
            int node = order.top();
            order.pop();
            if (sccId[node] == -1) {
                shrinkNodes(node, revAdj, sccId, sccCount);
                sccCount++;
            }
        }

        vector<bool> hasCrystal(sccCount, false);
        vector<bool> hasIncoming(sccCount, false);
        for (int crystal : crystals) {
            hasCrystal[sccId[crystal]] = true; // Mark SCCs containing crystals
        }

        // Build the SCC graph
        vector<unordered_set<int>> sccGraph(sccCount);
        for (int i = 0; i < flowFrom.size(); i++) {
            int u = sccId[flowFrom[i]], v = sccId[flowTo[i]];
            if (u != v) {
                sccGraph[u].insert(v); // Connect shrunk nodes
            }
        }

        for (int u = 0; u < sccCount; u++) {
            for (int v : sccGraph[u]) {
                hasIncoming[v] = true; // Mark incoming edges
            }
        }

        // Collect SCCs that do not have crystals and do not have incoming edges
        vector<int> sccWithoutCrystal, sccWithoutIncoming;
        for (int i = 0; i < sccCount; i++) {
            if (!hasCrystal[i]) {
                sccWithoutCrystal.push_back(i);
            }
            if (!hasIncoming[i]) {
                sccWithoutIncoming.push_back(i);
            }
        }

        // Use binary search to find how many SCCs are both without crystals and without incoming edges
        int runesNeeded = 0;
        for (int scc : sccWithoutCrystal) {
            if (binary_search(sccWithoutIncoming.begin(), sccWithoutIncoming.end(), scc)) {
                runesNeeded++; // Need a rune for this SCC
            }
        }

        return runesNeeded;
    }

private:
    void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& order) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, order);
            }
        }
        order.push(node); // Push node to the stack after finishing its neighbors
    }

    void shrinkNodes(int node, const vector<vector<int>>& revAdj, vector<int>& sccId, int sccCount) {
        sccId[node] = sccCount; // Mark the current node with its SCC ID
        for (int neighbor : revAdj[node]) {
            if (sccId[neighbor] == -1) {
                shrinkNodes(neighbor, revAdj, sccId, sccCount); // Recursively mark all nodes in this SCC
            }
        }
    }
};

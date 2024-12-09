class Solution {
public:
    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {
        // Build adjacency list and reverse adjacency list
        vector<vector<int>> adj(n), revAdj(n);
        for (int i = 0; i < flowFrom.size(); i++) {
            adj[flowFrom[i]].push_back(flowTo[i]);
            revAdj[flowTo[i]].push_back(flowFrom[i]);
        }

        // Step 1: Perform DFS to determine the order of nodes
        vector<bool> visited(n, false);
        stack<int> order;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, order);
            }
        }

        // Step 2: Find SCCs using the reverse graph and track properties
        vector<int> sccId(n, -1);
        vector<bool> hasCrystal; // To track if SCC has crystals
        vector<bool> hasIncoming; // To track incoming edges for SCCs
        int sccCount = 0;

        // Step 2a: Initialize properties
        while (!order.empty()) {
            int node = order.top();
            order.pop();
            if (sccId[node] == -1) {
                hasCrystal.push_back(false); // Initialize SCC crystal tracking
                hasIncoming.push_back(false); // Initialize incoming edge tracking
                shrinkNodes(node, revAdj, sccId, sccCount, hasCrystal);
                sccCount++;
            }
        }

        // Step 3: Mark the SCCs containing crystals
        for (int crystal : crystals) {
            hasCrystal[sccId[crystal]] = true; // Mark that this SCC has crystals
        }

        // Step 4: Check incoming edges to SCCs based on flowFrom and flowTo
        for (int i = 0; i < flowFrom.size(); i++) {
            int u = sccId[flowFrom[i]], v = sccId[flowTo[i]];
            if (u != v) {
                hasIncoming[v] = true; // Mark that SCC v has an incoming edge
            }
        }

        // Step 5: Count SCCs that do not have crystals and do not have incoming edges
        int runesNeeded = 0;
        for (int i = 0; i < sccCount; i++) {
            // Check if the SCC has no crystals and no incoming edges
            if (!hasCrystal[i] && !hasIncoming[i]) {
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

    void shrinkNodes(int node, const vector<vector<int>>& revAdj, vector<int>& sccId, int sccCount, vector<bool>& hasCrystal) {
        sccId[node] = sccCount; // Mark the current node with its SCC ID
        // Collect nodes in the current SCC
        for (int neighbor : revAdj[node]) {
            if (sccId[neighbor] == -1) {
                shrinkNodes(neighbor, revAdj, sccId, sccCount, hasCrystal); // Recursively mark all nodes in this SCC
            }
        }
    }
};

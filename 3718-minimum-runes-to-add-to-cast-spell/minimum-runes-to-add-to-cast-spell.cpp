class Solution {
public:
    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {
        vector<vector<int>> adj(n), revAdj(n);
        for (int i = 0; i < flowFrom.size(); i++) {
            adj[flowFrom[i]].push_back(flowTo[i]);
            revAdj[flowTo[i]].push_back(flowFrom[i]);
        }

        // Perform DFS to determine the order of nodes
        vector<bool> visited(n, false);
        stack<int> order;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, order);
            }
        }

        // Find SCCs using the reverse graph
        vector<int> sccId(n, -1);
        int sccCount = 0;
        vector<int> sccProperties; 

        while (!order.empty()) {
            int node = order.top();
            order.pop();
            if (sccId[node] == -1) {
                sccProperties.push_back(0);
                shrinkNodes(node, revAdj, sccId, sccProperties, sccCount);
                sccCount++;
            }
        }

        // Mark the SCCs containing crystals
        for (int crystal : crystals) {
            sccProperties[sccId[crystal]] |= 1;
        }

        // Check incoming edges to SCCs
        vector<bool> hasIncoming(sccCount, false);
        for (int i = 0; i < flowFrom.size(); i++) {
            int u = sccId[flowFrom[i]], v = sccId[flowTo[i]];
            if (u != v) {
                hasIncoming[v] = true; 
            }
        }

        // Count SCCs that do not have crystals and do not have incoming edges
        int runesNeeded = 0;
        for (int i = 0; i < sccCount; i++) {
            if (!(sccProperties[i] & 1) && !hasIncoming[i]) {
                runesNeeded++; 
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
        order.push(node); 
    }

    void shrinkNodes(int node, const vector<vector<int>>& revAdj, vector<int>& sccId, vector<int>& sccProperties, int sccCount) {
        sccId[node] = sccCount; 
        for (int neighbor : revAdj[node]) {
            if (sccId[neighbor] == -1) {
                shrinkNodes(neighbor, revAdj, sccId, sccProperties, sccCount); 
            }
        }
    }
};

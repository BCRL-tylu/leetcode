#include <vector>
#include <stack>

class Solution {
public:
    int minRunesToAdd(int n, std::vector<int>& crystals, std::vector<int>& flowFrom, std::vector<int>& flowTo) {
        // Build adjacency list and reverse adjacency list
        std::vector<std::vector<int>> adj(n), revAdj(n);
        for (size_t i = 0; i < flowFrom.size(); i++) {
            adj[flowFrom[i]].push_back(flowTo[i]);
            revAdj[flowTo[i]].push_back(flowFrom[i]);
        }

        // Perform DFS to determine the order of nodes
        std::vector<bool> visited(n, false);
        std::stack<int> order;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, order);
            }
        }

        // Find SCCs using the reverse graph
        std::vector<int> sccId(n, -1);
        int sccCount = 0;
        while (!order.empty()) {
            int node = order.top();
            order.pop();
            if (sccId[node] == -1) {
                shrinkNodes(node, revAdj, sccId, sccCount);
                sccCount++;
            }
        }

        // Now that we have the total number of SCCs, we can initialize the properties vector
        vector<bool> hasCrystal(sccCount, false); // Track if SCC contains crystals

        // Mark the SCCs containing crystals
        for (int crystal : crystals) {
            hasCrystal[sccId[crystal]] = true; // Mark that the SCC contains a crystal
        }

        // Check incoming edges to SCCs and count SCCs that do not have crystals and do not have incoming edges
        vector<bool> hasIncoming(sccCount, true);
        int runesNeeded = 0;

        for (size_t i = 0; i < flowFrom.size(); i++) {
            int u = sccId[flowFrom[i]], v = sccId[flowTo[i]];
            if (u != v) {
                hasIncoming[v] = false; // Mark incoming edges for SCC v
            }
        }

        // Count SCCs without crystals and without incoming edges
        for (int i = 0; i < sccCount; i++) {
            if (!hasCrystal[i] && hasIncoming[i]) {
                runesNeeded++; // Need a rune for this SCC
            }
        }
        return runesNeeded;
    }

private:
    void dfs(int node, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::stack<int>& order) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, order);
            }
        }
        order.push(node); // Push node to the stack after finishing its neighbors
    }

    void shrinkNodes(int node, const std::vector<std::vector<int>>& revAdj, std::vector<int>& sccId, int sccCount) {
        sccId[node] = sccCount; // Mark the current node with its SCC ID
        // Collect nodes in the current SCC
        for (int neighbor : revAdj[node]) {
            if (sccId[neighbor] == -1) {
                shrinkNodes(neighbor, revAdj, sccId, sccCount);
            }
        }
    }
};

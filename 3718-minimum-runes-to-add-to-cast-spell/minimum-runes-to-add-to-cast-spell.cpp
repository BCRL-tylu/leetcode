#include <vector>
#include <stack>

class Solution {
public:
    int minRunesToAdd(int n, std::vector<int>& crystals, std::vector<int>& flowFrom, std::vector<int>& flowTo) {
        std::vector<std::vector<int>> adj(n), revAdj(n);
        std::vector<int> sccId(n, -1), sccProperties;
        std::vector<bool> visited(n, false);
        std::stack<int> order;

        // Build adjacency and reverse adjacency lists
        for (size_t i = 0; i < flowFrom.size(); i++) {
            adj[flowFrom[i]].push_back(flowTo[i]);
            revAdj[flowTo[i]].push_back(flowFrom[i]);
        }

        // Perform DFS to determine the finishing order of nodes
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, order);
            }
        }

        // Identify strongly connected components (SCCs)
        int sccCount = 0;
        while (!order.empty()) {
            int node = order.top();
            order.pop();
            if (sccId[node] == -1) {
                sccProperties.push_back(0); // Initialize new SCC properties
                shrinkNodes(node, revAdj, sccId, sccCount);
                sccCount++;
            }
        }

        // Mark SCCs that contain crystals
        for (int crystal : crystals) {
            sccProperties[sccId[crystal]] |= 1; // Set crystal bit (bit 0)
        }

        // Check incoming edges to SCCs
        std::vector<bool> hasIncoming(sccCount, false);
        for (size_t i = 0; i < flowFrom.size(); i++) {
            int u = sccId[flowFrom[i]], v = sccId[flowTo[i]];
            if (u != v) {
                hasIncoming[v] = true; // Mark incoming edges for SCC v
            }
        }

        // Count SCCs that do not have crystals and do not have incoming edges
        int runesNeeded = 0;
        for (int i = 0; i < sccCount; i++) {
            if (!(sccProperties[i] & 1) && !hasIncoming[i]) {
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
        for (int neighbor : revAdj[node]) {
            if (sccId[neighbor] == -1) {
                shrinkNodes(neighbor, revAdj, sccId, sccCount); // Recursively mark all nodes in this SCC
            }
        }
    }
};

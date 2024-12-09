#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>

class Solution {
public:
    int minRunesToAdd(int n, std::vector<int>& crystals, std::vector<int>& flowFrom, std::vector<int>& flowTo) {
        std::unordered_map<int, std::unordered_set<int>> adj, revAdj;

        // Build adjacency list and reverse adjacency list
        for (int i = 0; i < flowFrom.size(); i++) {
            adj[flowFrom[i]].insert(flowTo[i]);
            revAdj[flowTo[i]].insert(flowFrom[i]);
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
        std::vector<int> sccProperties;

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
            sccProperties[sccId[crystal]] |= 1; // Set crystal bit (bit 0)
        }

        // Check incoming edges to SCCs
        std::vector<bool> hasIncoming(sccCount, false);
        for (int i = 0; i < flowFrom.size(); i++) {
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
    void dfs(int node, const std::unordered_map<int, std::unordered_set<int>>& adj, std::vector<bool>& visited, std::stack<int>& order) {
        visited[node] = true;
        auto it = adj.find(node);
        if (it != adj.end()) {
            for (int neighbor : it->second) { // Access the set safely
                if (!visited[neighbor]) {
                    dfs(neighbor, adj, visited, order);
                }
            }
        }
        order.push(node); // Push node to the stack after finishing its neighbors
    }

    void shrinkNodes(int node, const std::unordered_map<int, std::unordered_set<int>>& revAdj, std::vector<int>& sccId, std::vector<int>& sccProperties, int sccCount) {
        sccId[node] = sccCount; // Mark the current node with its SCC ID
        auto it = revAdj.find(node);
        if (it != revAdj.end()) {
            for (int neighbor : it->second) { // Access the set safely
                if (sccId[neighbor] == -1) {
                    shrinkNodes(neighbor, revAdj, sccId, sccProperties, sccCount); // Recursively mark all nodes in this SCC
                }
            }
        }
    }
};

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

        // Step 1: Perform DFS to determine the order of nodes
        std::vector<int> order;
        std::vector<char> visited(n, 0);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, order);
            }
        }

        // Step 2: Find SCCs using the reverse graph
        std::vector<int> sccId(n, -1);
        int sccCount = 0;
        std::vector<int> sccProperties; // To store properties of each SCC
        sccProperties.reserve(n); // Reserve space based on maximum possible SCCs

        for (int i = order.size() - 1; i >= 0; i--) {
            int node = order[i];
            if (sccId[node] == -1) {
                sccProperties.push_back(0); // Initialize new SCC properties
                shrinkNodes(node, revAdj, sccId, sccCount, sccProperties);
                sccCount++;
            }
        }

        // Step 3: Mark the SCCs containing crystals
        for (int crystal : crystals) {
            sccProperties[sccId[crystal]] |= 1; // Set crystal bit (bit 0)
        }

        // Step 4: Check incoming edges to SCCs
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
            if ((sccProperties[i] & 1) == 0 && !hasIncoming[i]) {
                runesNeeded++; // Need a rune for this SCC
            }
        }
        return runesNeeded;
    }

private:
    void dfs(int node, const std::vector<std::vector<int>>& adj, std::vector<char>& visited, std::vector<int>& order) {
        visited[node] = 1;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, order);
            }
        }
        order.push_back(node); // Push node to the order vector after finishing its neighbors
    }

    void shrinkNodes(int node, const std::vector<std::vector<int>>& revAdj, std::vector<int>& sccId, int sccCount, std::vector<int>& sccProperties) {
        sccId[node] = sccCount; // Mark the current node with its SCC ID
        // Collect nodes in the current SCC iteratively to avoid recursion depth issues
        std::stack<int> stack;
        stack.push(node);
        
        while (!stack.empty()) {
            int currNode = stack.top();
            stack.pop();
            for (int neighbor : revAdj[currNode]) {
                if (sccId[neighbor] == -1) {
                    sccId[neighbor] = sccCount; // Mark SCC ID
                    stack.push(neighbor);
                }
            }
        }
    }
};

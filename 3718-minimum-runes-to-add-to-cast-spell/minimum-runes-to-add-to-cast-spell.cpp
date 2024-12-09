#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {
        // Initialize adjacency list using unordered_multimap
        unordered_multimap<int, int> adj; // For normal graph
        unordered_multimap<int, int> revAdj; // For reversed graph
        
        // Build the graph
        for (int i = 0; i < flowFrom.size(); i++) {
            adj.insert({flowFrom[i], flowTo[i]});
            revAdj.insert({flowTo[i], flowFrom[i]});
        }

        // Perform DFS to determine the order of nodes
        vector<bool> visited(n, false);
        stack<int> order;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, visited, order, adj);
            }
        }

        // Find SCCs using the reverse graph
        vector<int> sccId(n, -1);
        int sccCount = 0;
        vector<int> sccProperties; // To store properties of each SCC

        while (!order.empty()) {
            int node = order.top();
            order.pop();
            if (sccId[node] == -1) {
                sccProperties.push_back(0); // Initialize new SCC properties
                shrinkNodes(node, sccId, sccCount, revAdj, sccProperties);
                sccCount++;
            }
        }

        // Mark the SCCs containing crystals
        for (int crystal : crystals) {
            sccProperties[sccId[crystal]] |= 1; // Set crystal bit (bit 0)
        }

        // Check incoming edges to SCCs
        vector<bool> hasIncoming(sccCount, false);
        for (int i = 0; i < flowFrom.size(); i++) {
            int u = sccId[flowFrom[i]], v = sccId[flowTo[i]];
            if (u != v) {
                hasIncoming[v] = true; // Mark incoming edges for SCC v
            }
        }

        // Count SCCs that do not have crystals and do not have incoming edges
        int runesNeeded = 0;
        for (int i = 0; i < sccCount; i++) {
            // Check if the SCC has no crystals and no incoming edges
            if (!(sccProperties[i] & 1) && !hasIncoming[i]) {
                runesNeeded++; // Need a rune for this SCC
            }
        }

        return runesNeeded;
    }

private:
    void dfs(int node, vector<bool>& visited, stack<int>& order, unordered_multimap<int, int>& adj) {
        visited[node] = true;
        auto range = adj.equal_range(node);
        for (auto it = range.first; it != range.second; ++it) {
            int neighbor = it->second;
            if (!visited[neighbor]) {
                dfs(neighbor, visited, order, adj);
            }
        }
        order.push(node); // Push node to the stack after finishing its neighbors
    }

    void shrinkNodes(int node, vector<int>& sccId, int sccCount, unordered_multimap<int, int>& revAdj, vector<int>& sccProperties) {
        sccId[node] = sccCount; // Mark the current node with its SCC ID
        // Collect nodes in the current SCC
        auto range = revAdj.equal_range(node);
        for (auto it = range.first; it != range.second; ++it) {
            int neighbor = it->second;
            if (sccId[neighbor] == -1) {
                shrinkNodes(neighbor, sccId, sccCount, revAdj, sccProperties); // Recursively mark all nodes in this SCC
            }
        }
    }
};

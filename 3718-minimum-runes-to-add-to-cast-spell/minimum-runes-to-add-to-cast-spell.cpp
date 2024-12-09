#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {
        // Build adjacency list and reverse adjacency list
        vector<vector<int>> adj(n), revAdj(n);
        for (int i = 0; i < flowFrom.size(); i++) {
            adj[flowFrom[i]].push_back(flowTo[i]);
            revAdj[flowTo[i]].push_back(flowFrom[i]);
        }
        // Step 1: Find the finishing order using DFS
        vector<bool> visited(n, false);
        stack<int> order;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, order);
            }
        }
        // Step 2: Identify shrunk nodes (SCCs)
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

        // Step 3: Build SCC-level graph and check properties
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

        // Step 4: Count SCCs that need additional runes
        for (int u = 0; u < sccCount; u++) {
            for (int v : sccGraph[u]) {
                hasIncoming[v] = true; // Mark incoming edges
            }
        }

        // Calculate the number of additional runes needed
        int runesNeeded = 0;
        for (int i = 0; i < sccCount; i++) {
            if (!hasIncoming[i] && !hasCrystal[i]) {
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

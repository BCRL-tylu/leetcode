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

        // Step 1: Perform DFS to find the finishing order
        vector<bool> visited(n, false);
        stack<int> order;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) dfs1(i, adj, visited, order);
        }

        // Step 2: Find strongly connected components (SCCs) using reverse graph
        vector<int> sccId(n, -1);
        int sccCount = 0;
        while (!order.empty()) {
            int node = order.top();
            order.pop();
            if (sccId[node] == -1) {
                dfs2(node, revAdj, sccId, sccCount);
                sccCount++;
            }
        }

        // Step 3: Build SCC-level graph and check properties
        vector<bool> hasCrystal(sccCount, false);
        vector<unordered_set<int>> sccGraph(sccCount);
        for (int crystal : crystals) {
            hasCrystal[sccId[crystal]] = true;
        }
        for (int i = 0; i < flowFrom.size(); i++) {
            int u = sccId[flowFrom[i]], v = sccId[flowTo[i]];
            if (u != v) {
                sccGraph[u].insert(v);
            }
        }

        // Step 4: Count SCCs that need additional runes
        vector<bool> hasIncoming(sccCount, false);
        for (int u = 0; u < sccCount; u++) {
            for (int v : sccGraph[u]) {
                hasIncoming[v] = true;
            }
        }

        int runesNeeded = 0;
        for (int i = 0; i < sccCount; i++) {
            if (!hasIncoming[i] && !hasCrystal[i]) {
                runesNeeded++;
            }
        }

        return runesNeeded;
    }

private:
    void dfs1(int node, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& order) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) dfs1(neighbor, adj, visited, order);
        }
        order.push(node);
    }

    void dfs2(int node, const vector<vector<int>>& revAdj, vector<int>& sccId, int sccCount) {
        sccId[node] = sccCount;
        for (int neighbor : revAdj[node]) {
            if (sccId[neighbor] == -1) dfs2(neighbor, revAdj, sccId, sccCount);
        }
    }
};

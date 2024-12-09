#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {
        // Build adjacency list
        vector<vector<int>> adj(n);
        for (int i = 0; i < flowFrom.size(); i++) {
            adj[flowFrom[i]].push_back(flowTo[i]);
        }

        // Tarjan's algorithm variables
        vector<int> discoveryTime(n, -1), lowLink(n, -1);
        vector<bool> onStack(n, false);
        stack<int> dfsStack;
        vector<int> sccId(n, -1);
        int time = 0, sccCount = 0;

        // Tarjan's algorithm to find SCCs
        for (int i = 0; i < n; i++) {
            if (discoveryTime[i] == -1) {
                tarjanDFS(i, time, adj, discoveryTime, lowLink, onStack, dfsStack, sccId, sccCount);
            }
        }

        // Determine properties of SCCs
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

        // Count SCCs with no incoming edges and no crystals
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
    void tarjanDFS(int node, int& time, const vector<vector<int>>& adj,
                   vector<int>& discoveryTime, vector<int>& lowLink,
                   vector<bool>& onStack, stack<int>& dfsStack,
                   vector<int>& sccId, int& sccCount) {
        discoveryTime[node] = lowLink[node] = time++;
        dfsStack.push(node);
        onStack[node] = true;

        for (int neighbor : adj[node]) {
            if (discoveryTime[neighbor] == -1) {
                // Neighbor not visited, recurse
                tarjanDFS(neighbor, time, adj, discoveryTime, lowLink, onStack, dfsStack, sccId, sccCount);
                lowLink[node] = min(lowLink[node], lowLink[neighbor]);
            } else if (onStack[neighbor]) {
                // Back edge to an ancestor
                lowLink[node] = min(lowLink[node], discoveryTime[neighbor]);
            }
        }

        // If node is root of an SCC
        if (lowLink[node] == discoveryTime[node]) {
            while (true) {
                int u = dfsStack.top();
                dfsStack.pop();
                onStack[u] = false;
                sccId[u] = sccCount;
                if (u == node) break;
            }
            sccCount++;
        }
    }
};

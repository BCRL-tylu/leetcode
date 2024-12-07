#include <vector>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> pii; // Shorthand for a pair of integers
typedef vector<int> vi; // Shorthand for a vector of integers
const int MAX_NODES = 100000;
static vector<int> adj1[MAX_NODES], adj2[MAX_NODES]; // Static adjacency lists

class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1; // Number of nodes in tree 1
        int m = edges2.size() + 1; // Number of nodes in tree 2

        // Step 1: Build adjacency lists
        for (auto& edge : edges1) {
            adj1[edge[0]].push_back(edge[1]);
            adj1[edge[1]].push_back(edge[0]);
        }
        for (auto& edge : edges2) {
            adj2[edge[0]].push_back(edge[1]);
            adj2[edge[1]].push_back(edge[0]);
        }

        // Step 2: BFS for labeling nodes in tree 1
        vi labels1(n, -1); // -1 means unvisited
        vi labelCounts1(2, 0); // Count of nodes with labels 0 and 1
        queue<int> q;

        q.push(0); // Start BFS from node 0
        labels1[0] = 0; // Initial label
        labelCounts1[0]++;
        

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (int neighbor : adj1[current]) {
                if (labels1[neighbor] == -1) { // If unvisited
                    labels1[neighbor] = labels1[current] ^ 1; // Use XOR to alternate label
                    labelCounts1[labels1[neighbor]]++;
                    q.push(neighbor);
                }
            }
        }

        // Step 3: BFS for counting labels in tree 2
        vi labelCounts2(2, 0);
        vi visited2(m, 0); // Use `vi` for boolean-like visited array
        queue<pii> q2; // Store (node, label) pairs

        q2.push({0, 0}); // Start BFS from node 0
        visited2[0] = true;
        labelCounts2[0]++;

        int newLabel;
        while (!q2.empty()) {
            auto [current, label] = q2.front();
            q2.pop();
            for (int neighbor : adj2[current]) {
                if (!visited2[neighbor]) { // If unvisited
                    newLabel = label ^ 1; // Alternate label using XOR
                    labelCounts2[newLabel]++;
                    visited2[neighbor] = true;
                    q2.push({neighbor, newLabel});
                }
            }
        }

        // Step 4: Compute results
        int maxLabel2 = max(labelCounts2[0], labelCounts2[1]);
        vi result(n);
        for (int i = 0; i < n; i++) {
            result[i] = labelCounts1[labels1[i]] + maxLabel2;
            adj1[i].clear();
        }
        // Clear adjacency lists (necessary for LeetCode environment)
        for (int i = 0; i < m; i++) adj2[i].clear();
        return result;
    }
};

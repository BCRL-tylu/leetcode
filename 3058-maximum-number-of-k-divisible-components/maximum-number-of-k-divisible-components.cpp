#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<vector<int>> tree(n);
        vector<int> visited(n, 0);

        // Build adjacency list for the tree
        for (auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        int components = 0;

        // Helper DFS function
        function<long long(int)> dfs = [&](int node) {
            visited[node] = 1;
            long long subtreeSum = values[node];

            for (int neighbor : tree[node]) {
                if (!visited[neighbor]) {
                    long long childSum = dfs(neighbor);
                    if (childSum % k == 0) {
                        // If the child subtree is divisible by k, we can dissociate it
                        components++;
                    } else {
                        // Otherwise, add its sum to the current node's sum
                        subtreeSum += childSum;
                    }
                }
            }

            return subtreeSum;
        };

        // Start DFS from node 0 (arbitrary root)
        long long totalSum = dfs(0);

        // If the entire tree sum is divisible by k, count the root as a valid component
        if (totalSum % k == 0) {
            components++;
        }

        return components;
    }
};

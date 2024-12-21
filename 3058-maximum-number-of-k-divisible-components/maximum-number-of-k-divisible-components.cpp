#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int>> tree;
    vector<int> values;
    int components;
    int k;

    long long dfs(int node, int parent) {
        long long subtreeSum = values[node];

        for (int neighbor : tree[node]) {
            if (neighbor != parent) {
                long long childSum = dfs(neighbor, node);
                if (childSum % k == 0) {
                    // If the child subtree is divisible by k, we can dissociate it
                    components++;
                } else {
                    // Otherwise, add its sum to the current node's sum
                    subtreeSum += childSum;
                }
            }
        }
        // If the current node's subtree sum is divisible by k, it contributes a component
        if (parent == -1 && subtreeSum % k == 0) {
            components++;
        }
        return subtreeSum;
    }

public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        this->tree.assign(n, vector<int>());
        this->values = values;
        this->components = 0;
        this->k = k;

        // Build adjacency list for the tree
        for (auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        // Start DFS from node 0 (arbitrary root), with no parent (-1)
        dfs(0, -1);

        return components;
    }
};

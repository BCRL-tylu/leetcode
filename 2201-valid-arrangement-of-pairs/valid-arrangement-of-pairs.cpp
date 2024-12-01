#include <vector>
#include <unordered_map>
#include <stack>

class Solution {
public:
    std::vector<std::vector<int>> validArrangement(std::vector<std::vector<int>>& pairs) {
        // Step 1: Build adjacency list and compute degree
        std::unordered_map<int, std::vector<int>> adj;
        std::unordered_map<int, int> degree;

        for (const auto& edge : pairs) {
            int from = edge[0], to = edge[1];
            adj[from].push_back(to);
            degree[from]--;
            degree[to]++;
        }
        // Step 2: Find the start vertex
        int start = -1;
        for (const auto& [node, deg] : degree) {
            if (deg == -1) {
                start = node; // Start of the Eulerian path
                break;
            }
        }
        if (start == -1) {
            start = pairs[0][0]; // Arbitrary start if no imbalanced nodes
        }
        // Step 3: Hierholzer’s Algorithm to find Eulerian path
        std::stack<int> stack;
        std::vector<int> path;
        std::vector<std::vector<int>> result;
        stack.push(start);
        int node,next;
        while (path.empty()) {
           node = stack.top();
            if (!adj[node].empty()) {
                stack.push(adj[node].back());
                adj[node].pop_back();
            } else {
                path.push_back(node);
                stack.pop();
            }
        }
        while (!stack.empty()) {
            node = stack.top();
            if (!adj[node].empty()) {
                stack.push(adj[node].back());
                adj[node].pop_back();
            } else {
                path.push_back(node);
                stack.pop();
                result.push_back({node, path[path.size()-2]});
            }
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

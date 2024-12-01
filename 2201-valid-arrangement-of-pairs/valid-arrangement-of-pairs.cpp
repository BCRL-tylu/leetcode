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
        stack.push(start);

        while (!stack.empty()) {
            int node = stack.top();
            if (!adj[node].empty()) {
                int next = adj[node].back();  // Get the last edge in the adjacency list
                adj[node].pop_back();          // Remove that edge from the list
                stack.push(next);              // Push the next node onto the stack
            } else {
                path.insert(path.begin(), node); // Insert at the front
                stack.pop();                      // Backtrack
            }
        }

        // Step 4: Reconstruct result as pairs
        std::vector<std::vector<int>> result;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            result.push_back({path[i], path[i + 1]});
        }

        return result;
    }
};

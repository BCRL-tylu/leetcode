class Solution {
public:
    std::vector<std::vector<int>> validArrangement(std::vector<std::vector<int>>& pairs) {
        // Step 1: Build adjacency list and compute degree
        unordered_map<int, std::vector<int>> adj;
        unordered_map<int, int> degree;

        for (const auto& edge : pairs) {
            int from = edge[0], to = edge[1];
            adj[from].push_back(to);
            degree[from]--;
            degree[to]++;
        }
        // Step 2: Find the start vertex
        int start = start = pairs[0][0];
        for (const auto& [node, deg] : degree) {
            if (deg == -1) {
                start = node; // Start of the Eulerian path
                break;
            }
        }
        // Step 3: Hierholzer’s Algorithm to find Eulerian path
        stack<int> stack;
        vector<int> path;
        vector<vector<int>> result;
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
                result.push_back({node, path.back()});
                path.push_back(node);
                stack.pop();
            }
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

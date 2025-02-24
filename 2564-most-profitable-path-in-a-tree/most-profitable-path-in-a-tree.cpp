class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = amount.size();
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Bob's path tracking with efficient backtracking DFS
        vector<int> bobp;
        vector<int> visited(n, 0);
        function<bool(int)> findBobPath = [&](int node) {
            bobp.push_back(node);
            if (node == bob) return true;  // Found Bob, stop recursion
            visited[node] = 1;
            for (int son : adj[node]) {
                if (!visited[son] && findBobPath(son)) {
                    return true;
                }
            }
            bobp.pop_back(); // Backtrack if not on the path
            return false;
        };

        findBobPath(0);
        reverse(bobp.begin(), bobp.end());
        // Bob clears amounts on his path
        vector<int> amount_clear_time(n, INT_MAX);
        for (int i = 0; i < bobp.size(); i++) {
            amount_clear_time[bobp[i]] = i;
        }

        int max_profit = INT_MIN;

        // Alice's DFS (iterative)
        stack<vector<int>> aq; // {current node, profit so far, time}
        vector<int> visited_alice(n, 0);
        aq.push({0, 0, 0});

        while (!aq.empty()) {
            vector<int> tp = aq.top();
            aq.pop();
            int cnode = tp[0], profit = tp[1], time = tp[2];
            if (visited_alice[cnode]) continue;
            visited_alice[cnode] = 1;
            // Calculate profit at the current node
            if (amount_clear_time[cnode] == time) {
                profit += amount[cnode]>>1;
            } else if (amount_clear_time[cnode] > time) {
                profit += amount[cnode];
            }
            bool isLeaf = true;
            for (int son : adj[cnode]) {
                if (!visited_alice[son]) {
                    isLeaf = false;
                    aq.push({son, profit, time + 1});
                }
            }
            if (isLeaf) {
                max_profit = max(max_profit, profit);
            }
        }
        return max_profit;
    }
};
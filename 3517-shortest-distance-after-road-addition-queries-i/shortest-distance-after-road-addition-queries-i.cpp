class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> from(n);
        vector<int> dp(n);
        std::iota(dp.begin(), dp.end(), 0);
        int m = queries.size();
        vector<int> ans(m);
        for (int i = 0; i < m; ++i) {
            int u = queries[i][0], v = queries[i][1];
            from[v].emplace_back(u);
            if (1 + dp[u] < dp[v]) {
                dp[v] = 1 + dp[u];
                for (int j = 1 + v; j < n; ++j) {
                    dp[j] = std::min(dp[j], 1 + dp[j - 1]);
                    for (int k : from[j]) {
                        dp[j] = std::min(dp[j], 1 + dp[k]);
                    }
                }
            }
            ans[i] = dp.back();
        }
        return ans;
    }
};
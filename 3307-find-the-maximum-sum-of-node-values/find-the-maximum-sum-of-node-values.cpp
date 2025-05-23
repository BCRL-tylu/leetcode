class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        

        vector<array<long long,2>> dp(n);

        auto dfs = [&](auto&& self, int u, int p) -> void {
            long long val0 = nums[u];
            long long val1 = nums[u] ^ (long long)k;
            long long base = 0;
            int parity = 0;
            vector<long long> diffs;

            for (int v : adj[u]) if (v != p) {
                self(self, v, u);
                long long a0 = dp[v][0], a1 = dp[v][1];
                long long d  = a1 - a0;
                if (a1 >= a0) {
                    base   += a1;
                    parity ^= 1;
                } else {
                    base   += a0;
                }
                diffs.push_back(d);
            }

            if (diffs.empty()) {
                dp[u][0] = val0;
                dp[u][1] = val1;
            } else {
                long long bestFix = LLONG_MAX;
                for (auto &d : diffs)
                    bestFix = min(bestFix, llabs(d));
                dp[u][0] = max((val1 + base - (parity == 1 ? 0LL : bestFix)),
                                (val0 + base - (parity == 0 ? 0LL : bestFix)));
                dp[u][1] = max((val0 + base - (parity == 1 ? 0LL : bestFix)),
                                (val1 + base - (parity == 0 ? 0LL : bestFix)));
            }
        };

        dfs(dfs, 0, -1);
        return dp[0][0];
    }
};

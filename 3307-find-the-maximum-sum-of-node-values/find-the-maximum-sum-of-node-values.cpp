class Solution {
public:
    long long maximumValueSum(vector<int>& nums,
                              int k,
                              vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> adj(n);
        for(auto &e: edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // dp[u][0] = best sum if the parent-edge u→parent(u) is flipped 0 times
        // dp[u][1] = best sum if it’s flipped 1 time
        vector<array<long long,2>> dp(n);

        auto dfs = [&](auto&& self, int u, int p)->void{
            long long val0 = nums[u];
            long long val1 = nums[u] ^ (long long)k;

            long long base = 0;
            int      parity = 0;
            vector<long long> diffs;

            for(int v: adj[u]) if(v != p){
                self(self, v, u);
                long long a0 = dp[v][0],
                          a1 = dp[v][1],
                          d  = a1 - a0;
                if(a1 >= a0){
                    base   += a1;
                    parity ^= 1;
                } else {
                    base   += a0;
                }
                diffs.push_back(d);
            }

            if(diffs.empty()){
                // leaf
                dp[u][0] = val0;
                dp[u][1] = val1;
            } else {
                // minimal sacrifice to flip exactly one child's choice
                long long min_abs = LLONG_MAX;
                for(auto &d: diffs)
                    min_abs = min(min_abs, llabs(d));

                // best_even  = base - (parity==0 ? 0 : min_abs)
                // best_odd   = base - (parity==1 ? 0 : min_abs)
                long long best_even = base - (parity == 0 ? 0LL : min_abs);
                long long best_odd  = base - (parity == 1 ? 0LL : min_abs);

                // Now for a GENERAL node u:
                //   dp[u][0] = max( best_even + val0, best_odd  + val1 )
                //   dp[u][1] = max( best_even + val1, best_odd  + val0 )
                // But *for the root*, par=0 is the only legal choice!
                dp[u][0] = max(best_even + val0, best_odd + val1);
                dp[u][1] = max(best_even + val1, best_odd + val0);
            }
        };
        dfs(dfs, 0, -1);
        return dp[0][0];
    }
};

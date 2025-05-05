class Solution {
public:
    int numTilings(int n) {
        const int MOD = 1000000007;      // 1e9+7
        if (n == 0) return 1;

        vector<long long> dp(n+1), pre(n+1);
        dp[0] = 1;                       // empty board
        dp[1] = 1;                       // one vertical domino
        pre[0] = pre[1] = 0;             // no overhang possible
        for (int i = 2; i <= n; ++i) {
            pre[i] = (pre[i-1] + dp[i-2]) % MOD;
            dp[i]  = (dp[i-1] + dp[i-2] + 2LL * pre[i-1]) % MOD;
        }
        return dp[n];
    }
};

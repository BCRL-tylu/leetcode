class Solution {
public:
    long long maxCoins(vector<int>& lane1, vector<int>& lane2) {
        int n = lane1.size();
        if (n == 1) return max(lane1[0], lane2[0]);

        const long long NEG_INF = -1e18;
        vector<vector<long long>> dp(n, vector<long long>(3, NEG_INF));

        dp[0][0] = lane1[0];
        dp[0][1] = lane2[0];

        long long ans = max(dp[0][0], dp[0][1]);

        for (int i = 1; i < n; i++) {
            // Stay in lane 1 or restart fresh
            dp[i][0] = max({(long long)lane1[i], dp[i-1][0] + lane1[i]});
            // Stay in lane 2, switch from lane1, or restart fresh
            dp[i][1] = max({(long long)lane2[i], dp[i-1][1] + lane2[i], dp[i-1][0] + lane2[i]});
            // Switch from lane 2 back to lane 1 or stay in lane 1
            dp[i][2] = max({dp[i-1][1] + lane1[i], dp[i-1][2] + lane1[i]});
            ans = max({ans, dp[i][0], dp[i][1], dp[i][2]});
        }

        return ans;
    }
};

class Solution {
public:
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();

        vector<int> ps(n + 1, 0);
        for (int i = 0; i < n; i++) {
            ps[i + 1] = ps[i] + nums[i];
        }

        const int neg_inf = -1e8 - 1;
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, neg_inf)),
            local(k + 1, vector<int>(n + 1, neg_inf));

        for (int j = 0; j <= n; j++) {
            dp[0][j] = 0;
        }

        for (int i = 1; i <= k; i++) {
            int u = i * m;
            local[i][u] = dp[i - 1][u - m] + (ps[u] - ps[u - m]);
            dp[i][u] = local[i][u]; // Update dp for the first valid index
            for (int j = u + 1; j <= n; j++) {
                local[i][j] = max(local[i][j - 1] + nums[j - 1],
                                  dp[i - 1][j - m] + (ps[j] - ps[j - m]));
                dp[i][j] = max(dp[i][j - 1], local[i][j]);
            }
        }

        return dp[k][n];
    }
};

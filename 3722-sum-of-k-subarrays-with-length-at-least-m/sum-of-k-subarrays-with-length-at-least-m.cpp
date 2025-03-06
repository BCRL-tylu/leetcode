class Solution {
public:
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();

        vector<int> ps(n+1, 0);
        for (int i = 0; i < n; i++) {
            ps[i+1] = ps[i] + nums[i];
        }

        vector<vector<int>> dp(k+1, vector<int>(n+1, INT_MIN)),local(k+1, vector<int>(n+1, INT_MIN));
        
        for (int j = 0; j <= n; j++) {
            dp[0][j] = 0;
        }

        for (int i = 1; i <= k; i++) {
            for (int j = i * m; j <= n; j++) {
                if(j == i * m) {
                    local[i][j] = dp[i-1][j-m] + (ps[j] - ps[j-m]);
                } else {
                    local[i][j] = local[i][j-1] + nums[j-1];
                    local[i][j] = max(local[i][j], dp[i-1][j-m] + (ps[j] - ps[j-m]));
                }

                dp[i][j] = max(dp[i][j-1], local[i][j]);
            }
        }
        
        return dp[k][n];
    }
};

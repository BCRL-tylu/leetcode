class Solution {
public:
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();
        // Build prefix sum array, where ps[i] is the sum of the first i elements.
        vector<int> ps(n + 1, 0);
        for (int i = 0; i < n; i++) {
            ps[i + 1] = ps[i] + nums[i];
        }

        const int neg_inf = -1e8 - 1;
        // dp[i][j]: maximum sum using i subarrays from the first j elements.
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, neg_inf));
        // Base case: 0 subarrays yield a sum of 0.
        for (int j = 0; j <= n; j++) {
            dp[0][j] = 0;
        }
        
        // Outer loop: for each subarray count.
        for (int i = 1; i <= k; i++) {
            int start = i * m; // Minimum j index to form i subarrays.
            vector<int> newdp(n + 1, neg_inf);
            
            // Initialize the current subarray ending exactly at index start - 1.
            int curr = dp[i - 1][start - m] + (ps[start] - ps[start - m]);
            newdp[start] = curr;
            
            // Process indices j from start+1 to n.
            for (int j = start + 1; j <= n; j++) {
                // Option 1: Extend the previous subarray.
                // Option 2: Start a new subarray of length m ending at j - 1.
                curr = max(curr + nums[j - 1],
                           dp[i - 1][j - m] + (ps[j] - ps[j - m]));
                newdp[j] = max(newdp[j - 1], curr);
            }
            dp[i] = newdp;  // Update dp for the current subarray count.
        }
        
        return dp[k][n];
    }
};

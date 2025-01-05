class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size(); // Get the size of the input array.
        int max_n = *max_element(begin(nums), end(nums)); // Find the maximum value in the array.
        
        // Initialize a 2D DP array with dimensions (max_n + 1) x (max_n + 1).
        // dp[num][diff] stores the length of the longest subsequence ending at 'num'
        // with the last difference between consecutive elements equal to 'diff'.
        vector<vector<int>> dp(max_n + 1, vector<int>(max_n + 1, 0));
        
        int res = 1; // Variable to keep track of the maximum subsequence length.

        // Iterate over each number in the input array.
        for (int i = 0; i < n; i++) {
            int num = nums[i]; // Current number in the array.

            dp[num][max_n] = 1; // Start a new subsequence with 'num'.

            // Iterate through all potential previous numbers (1 to max_n).
            for (int j = 1; j <= max_n; j++) {
                if (dp[j][max_n] == 0) continue; // Skip if there's no valid subsequence ending at 'j'.
                
                int diff = abs(num - j); // Calculate the absolute difference between 'num' and 'j'.
                
                // Update the DP value for the current number and difference.
                dp[num][diff] = max(dp[num][diff], 1 + dp[j][diff]);    
                
                // Update the global result with the maximum subsequence length found so far.
                res = max(res, dp[num][diff]);
            }

            // Ensure non-increasing difference property by propagating maximum values downward.
            for (int j = max_n - 1; j >= 0; j--) {
                dp[num][j] = max(dp[num][j], dp[num][j + 1]);
            }
        }

        return res; // Return the length of the longest subsequence.
    }
};

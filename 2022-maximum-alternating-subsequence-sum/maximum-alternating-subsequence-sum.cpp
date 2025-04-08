class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n,vector<long long>(2,0));
        dp[0][0] = nums[0];

        for(int i =0;i<n-1;i++){
            dp[i+1][0] = max(dp[i][1]+nums[i+1],dp[i][0]);
            dp[i+1][1] = max(dp[i][0]-nums[i+1],dp[i][1]);
        }
        return dp[n-1][0];
    }
};

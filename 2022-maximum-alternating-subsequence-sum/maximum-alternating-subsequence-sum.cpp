class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n,vector<long long>(2));
        dp[0][0] = nums[0];
        for(int i =0;i<n-1;i++){
            int k = i+1;
            dp[k][0] = max(dp[i][1]+nums[k],dp[i][0]);
            dp[k][1] = max(dp[i][0]-nums[k],dp[i][1]);
        }
        return dp[n-1][0];
    }
};

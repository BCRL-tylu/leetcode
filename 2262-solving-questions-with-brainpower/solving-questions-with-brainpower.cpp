class Solution {
public:
    long long mostPoints(vector<vector<int>>& q) {
        long long n = q.size(),ans =0;
        vector<long long> dp(n+1,0);
        for(int i =1;i<=n;i++){
            dp[i]=max(dp[i],dp[i-1]);
            int ind = i+q[i-1][1]+1;
            if(ind>n){
                ans = max(ans,dp[i]+q[i-1][0]);
                continue;
            }
            dp[ind] = max(dp[ind],dp[i]+q[i-1][0]);
        }
        return max(ans,dp[n]);
    }
};
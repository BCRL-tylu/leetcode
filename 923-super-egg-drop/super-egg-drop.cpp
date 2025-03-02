class Solution {
public:
        int solve(int k,int n,vector<vector<int>>&dp){

        if(n==0) return 0;

        if(n==1) return 1;

        if(k==1){
            return n;
        }
        if(dp[k][n]!=-1){
            return dp[k][n];
        }
        int mini = INT_MAX;
        int l = 1,r = n;
        while(l<=r){
            int mid = (l+r)/2;
            int notBroken = solve(k,n-mid,dp);
            int broken = solve(k-1,mid-1,dp);
            int temp = 1 + max(notBroken,broken);
            mini = min(mini,temp);

            if(notBroken < broken){
                r = mid - 1;
            }else{
                l = mid + 1;
            }
        }
        return dp[k][n] = mini;
        }
    int superEggDrop(int k, int n) {
        //k-eggs
        //n-floor
        vector<vector<int>>dp(k+1,vector<int>(n+1,-1));
        return solve(k,n,dp);
    }
};
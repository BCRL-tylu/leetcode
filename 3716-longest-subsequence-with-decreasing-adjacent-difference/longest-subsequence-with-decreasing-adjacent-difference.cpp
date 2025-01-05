class Solution {
public:
    
   
    int longestSubsequence(vector<int>& v)
    {
          int n = v.size();
          vector<vector<int>> dp(305, vector<int>(305, 0));
          for(int i = 0; i<= 300; i++)
          {
              dp[v[n - 1]][i] = 1;
          }

           for(int i = n - 2; i >= 0; i--)
           {   
               int ans = 0;
               for(int j = 0; j <= 300; j++)
               {
                   int x = v[i] + j;
                   int y = v[i] - j;
                   if(x <= 300)
                   {
                      ans = max(ans, dp[x][j]);
                   }

                   if(y >= 0)
                   {
                         ans = max(ans, dp[y][j]);  
                   }
                   dp[v[i]][j] = max(1 + ans, dp[v[i]][j]);
                   //ans = max(ans, dp[v[i]][j]);
               }
           }

           int ans = 0;
           for(int i = 0; i <= 300; i++)
           {
              for(int j = 0; j <= 300; j++) ans = max(ans, dp[i][j]);
           }

           return ans;     
    }
};
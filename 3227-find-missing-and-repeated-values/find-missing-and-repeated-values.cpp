class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int n = grid.size(),m=n*n+1;
        vector<int> u(m,0),ans(2,0);
        for(int i =0; i<n;i++){
            for(int j =0;j<n;j++){
                if(++u[grid[i][j]] == 2){
                    ans[0] = grid[i][j];
                }
            }
        }
        for(int k = 1;k<m;k++){
            if(u[k] == 0){
                ans[1] = k;
            }
        }
        return ans;
    }
};
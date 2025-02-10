class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        vector<vector<int>> ans = grid;
        int n = grid.size();
        for(int i = 1; i<n; i++){
            vector<int> dia;
            for(int j = 0; j<n-i;j++){
                dia.push_back(grid[j][j+i]);
            }
            sort(dia.begin(), dia.end());
            int ind = 0;
            for(int j = 0; j<n-i;j++){
                ans[j][j+i]=dia[ind++];
            }
        }

        for(int i = 0; i<n; i++){
            vector<int> dia;
            for(int j = 0; j<n-i;j++){
                dia.push_back(grid[i+j][j]);
            }
            sort(dia.begin(), dia.end(), greater<int>());
            int ind = 0;
            for(int j = 0; j<n-i;j++){
                ans[j+i][j]=dia[ind++];
            }
        }
        return ans;    
    }
};
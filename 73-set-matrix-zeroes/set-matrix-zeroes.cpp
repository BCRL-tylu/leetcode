class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        unordered_set<int> r,c;
        int n = matrix.size(),m=matrix[0].size();
        for(int i =0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]==0){
                    r.insert(i);
                    c.insert(j);
                }
            }
        }
        for(auto k:r){
            fill(matrix[k].begin(), matrix[k].end(), 0);
        }
        for(auto k:c){
            for(int i=0;i<n;i++){
                matrix[i][k] =0;
            }
        }
    }
};
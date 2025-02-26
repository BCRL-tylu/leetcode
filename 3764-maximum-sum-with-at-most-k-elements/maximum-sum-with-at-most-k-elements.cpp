class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size(),m = grid[0].size();
        priority_queue<int>pq;
        for(int i =0; i<n;i++){
            int count =0;
            priority_queue<int>temp_pq;
            for(int j=0;j<m;j++){
                temp_pq.push(grid[i][j]);
            }
            for(int k =0; k<limits[i];k++){
                pq.push(temp_pq.top());
                temp_pq.pop();
            }
        }
        long long ans =0;
        for(int i = 0;i<k;i++){
            ans+=pq.top();
            pq.pop();
        }
        return ans;
    }
};
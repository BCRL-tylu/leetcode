class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n=nums.size(),m=queries.size();
        vector<int> temp(n,0);
        for(int i=0;i<m;i++){
            if(queries[i][1]<n-1){
                temp[queries[i][1]+1]++;
            }
            temp[queries[i][0]]--;
        }
        int toadd =0;
        for(int i=0;i<n;i++){
            toadd+=temp[i];
            if(nums[i]+toadd>0) return false;
        }

        return true;
    }
};
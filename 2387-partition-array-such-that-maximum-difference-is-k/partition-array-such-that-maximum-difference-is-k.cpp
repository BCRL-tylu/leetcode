class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int l = nums[0], r = nums[0],n=nums.size(),par = 1;
        for(int i =1; i<n;i++){
            r=nums[i];
            if(r-l<=k) continue;
            l = r;
            par++;
        }
        return par;
    }
};
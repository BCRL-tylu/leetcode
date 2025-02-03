class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int si=1, sd = 1, prev = nums[0], tem_si =1, tem_sd = 1;
        for(int i =1; i<(int)nums.size();i++){
            if(nums[i]<prev){
                prev=nums[i];
                sd = max(++tem_sd,sd);
                tem_si=1;
                continue;
            }
            if(nums[i]>prev){
                prev=nums[i];
                si = max(++tem_si,si);
                tem_sd=1;
                continue;
            }
            if(nums[i]=prev){
                tem_si=1;
                tem_sd=1;
                continue;
            }
        }
        return max(si, sd);
    }
};
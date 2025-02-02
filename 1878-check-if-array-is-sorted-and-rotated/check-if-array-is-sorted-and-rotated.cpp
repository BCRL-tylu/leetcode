class Solution {
public:
    bool check(vector<int>& nums) {
        int m = nums.size(), count = 0;
        for(int i = 0; i<m; i++){
            if(nums[i]<=nums[(i+1)%m]){
                continue;
            }
            if(++count>=2){
                return false;
            }
        }
        return true;
    }
};
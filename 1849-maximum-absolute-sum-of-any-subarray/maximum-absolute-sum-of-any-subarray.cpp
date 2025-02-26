class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size(), prefix = 0, mi = 0, ma = 0;
        for(int i =0;i<n;i++){
            prefix+=nums[i];
            mi = min(mi,prefix);
            ma = max(ma,prefix);
        }
        return ma-mi;
    }
};
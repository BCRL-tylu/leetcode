class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size(), prefix = 0, mi = 0, ma = 0;
        vector<int> ps;
        for(int i =0;i<n;i++){
            prefix+=nums[i];
            ps.push_back(prefix);
            mi = min(mi,prefix);
            ma = max(ma,prefix);
        }
        return ma-mi;
    }
};
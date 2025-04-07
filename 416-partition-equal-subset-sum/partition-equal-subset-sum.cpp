class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto i : nums) sum += i;
        if (sum & 1) return false;
        int target = sum>>1;
        vector<int> f(20001,0);
        for (int i = 1; i < nums.size(); i++)
            for (int l = target; l >= nums[i]; l--)
                f[l] = max(f[l], f[l - nums[i]] + nums[i]);
        return f[target] == target;
    }
};
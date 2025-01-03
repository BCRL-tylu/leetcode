class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        int n = nums.size();
        long long s = 0; // Use long long to prevent overflow
        for(int i = 0; i < n; i++) {
            s += nums[i];
        }

        int ways = 0;
        s = s - nums[n - 1];
        long long right = nums[n - 1]; // Use long long for right as well
        if(s >= right) ways++;

        for(int i = n - 2; i > 0; i--) {
            s -= nums[i];
            right += nums[i];
            if(s >= right) {
                ways++;
            }
        }
        return ways;
    }
};

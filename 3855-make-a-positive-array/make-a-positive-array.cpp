class Solution {
public:
    int makeArrayPositive(vector<int>& nums) {
        int ans = 0;
        long long sm = INT_MAX, mx = 1e18;
        long long a = nums[0], b = nums[1];

        for (int i = 2; i < nums.size(); ++i) {
            long long c = nums[i];
            sm = c + min(sm, a + b);
            if (sm <= 0) {
                c = mx;
                sm = mx;
                ans++;
            }
            a = b;
            b = c;
        }

        return ans;
    }
};

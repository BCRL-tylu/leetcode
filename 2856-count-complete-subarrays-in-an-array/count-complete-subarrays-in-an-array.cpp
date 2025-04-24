class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> all(nums.begin(), nums.end());
        int k = all.size();

        unordered_map<int,int> freq;
        int distinctInWindow = 0;
        long long ans = 0;
        int r = 0;

        for (int l = 0; l < n; ++l) {
            while (r < n && distinctInWindow < k) {
                if (freq[nums[r]]++ == 0)
                    ++distinctInWindow;
                ++r;
            }

            if (distinctInWindow == k)
                ans += (n - r + 1);

            if (--freq[nums[l]] == 0)
                --distinctInWindow;
        }

        return (int)ans;
    }
};

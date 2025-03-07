class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == n)
            return *max_element(nums.begin(), nums.end());
        if (k == 1) {
            std::unordered_map<int, int> freq;
            for (int num : nums) {
                freq[num]++;
            }

            int maxUnique = -1;
            for (const auto& [num, count] : freq) {
                if (count == 1) {
                    maxUnique = std::max(maxUnique, num);
                }
            }
            return maxUnique;
        }
        int a = nums[0], b = nums[n - 1];
        if (a == b)
            return -1;

        bool at = true, bt = true;
        for (int i = 1; i < n - 1; i++) {
            if (nums[i] == a) {
                at = false;
                continue;
            }
            if (nums[i] == b)
                bt = false;
        }
        if (at && bt) {
            return max(a, b);
        }
        if (at)
            return a;
        if (bt)
            return b;
        return -1;
    }
};
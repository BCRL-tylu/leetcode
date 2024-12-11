class Solution {
public:
    int maximumBeauty(std::vector<int>& nums, int k) {
        const int MAX_VAL = 100000;  // Maximum possible value for the problem
        std::vector<int> freq(MAX_VAL + 1, 0);  // Precompute a frequency array

        // Increment the frequency range for each number within [num - k, num + k]
        for (int num : nums) {
            int start = std::max(0, num - k);
            int end = std::min(MAX_VAL, num + k);
            freq[start]++;
            if (end + 1 <= MAX_VAL) freq[end + 1]--;
        }

        // Compute the prefix sum to determine the actual frequency at each index
        int max_beauty = 0;
        for (int i = 1; i <= MAX_VAL; ++i) {
            freq[i] += freq[i - 1];
            max_beauty = std::max(max_beauty, freq[i]);
        }

        return max_beauty;
    }
};

class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        unordered_map<int, long long> freq;
        long long goodPairs = 0;
        int n = nums.size();
        
        // One-pass: compute the number of good pairs on the fly.
        for (int i = 0; i < n; i++) {
            int diff = nums[i] - i;
            goodPairs += freq[diff];
            freq[diff]++;
        }
        
        // Total number of pairs.
        long long totalPairs = (long long)n * (n - 1) / 2;
        return totalPairs - goodPairs;
    }
};

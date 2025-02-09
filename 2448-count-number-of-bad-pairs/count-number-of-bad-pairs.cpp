class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        unordered_map<int, int> freq;
        long long n = nums.size(), goodPairs = 0;
        
        for (int i = 0; i < n; i++) {
            int key = nums[i] - i;
            goodPairs += freq[key]; // Count the number of previous occurrences
            freq[key]++; // Update the frequency
        }
        
        return n * (n - 1) / 2 - goodPairs;
    }
};

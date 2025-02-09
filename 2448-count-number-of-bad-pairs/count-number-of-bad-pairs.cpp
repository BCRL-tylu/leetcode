class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        int n = nums.size();
        // Compute the differences.
        vector<long long> diffs(n);
        for (int i = 0; i < n; i++) {
            diffs[i] = (long long)nums[i] - i;
        }
        
        // Sort the differences.
        sort(diffs.begin(), diffs.end());
        
        // Count good pairs by processing contiguous segments of equal diffs.
        long long goodPairs = 0;
        long long count = 1;  // count of current group
        for (int i = 1; i < n; i++) {
            if (diffs[i] == diffs[i - 1]) {
                count++;
            } else {
                // For a group of size 'count', the number of pairs is count*(count-1)/2.
                goodPairs += count * (count - 1) / 2;
                count = 1;
            }
        }
        // Add the last group.
        goodPairs += count * (count - 1) / 2;
        
        // Total pairs (i < j).
        long long totalPairs = (long long)n * (n - 1) / 2;
        return totalPairs - goodPairs;
    }
};

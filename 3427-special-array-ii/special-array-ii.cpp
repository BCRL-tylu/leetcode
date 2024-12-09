#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<bool> isArraySpecial(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
        int n = nums.size();
        std::vector<bool> rt(n - 1, true);
        std::vector<bool> results(queries.size());

        // Precompute the special conditions in `rt`
        for (int i = 0; i < n - 1; i++) {
            if ((nums[i + 1] - nums[i]) % 2 == 0) {
                rt[i] = false;
            }
        }

        // Use a prefix sum approach to quickly answer range queries
        std::vector<int> prefixFalseCount(n, 0);
        for (int i = 1; i < n; i++) {
            prefixFalseCount[i] = prefixFalseCount[i - 1] + (rt[i - 1] ? 0 : 1);
        }

        // Process each query
        for (int k = 0; k < queries.size(); k++) {
            int left = queries[k][0];
            int right = queries[k][1] - 1; // Convert to 0-based index

            // Check how many 'false' values are in the range
            int falseCount = prefixFalseCount[right + 1] - prefixFalseCount[left];

            results[k] = (falseCount == 0); // No false means all are true
        }
        return results;
    }
};

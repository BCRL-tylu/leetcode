#include <vector>
#include <unordered_map>
#include <functional>
#include <cmath>

class Solution {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {
        int totalSum = 0;
        int zeroCount = 0;

        // Calculate total sum and count zeros
        for (int num : nums) {
            if (num == 0) {
                zeroCount++;
            } else {
                totalSum += num;
            }
        }

        // Check if target is achievable with the non-zero sums
        if (target > totalSum || target < -totalSum) return 0;

        // Define the DFS function with memoization
        std::unordered_map<int, std::unordered_map<int, int>> memo;

        std::function<int(int, int)> dfs = [&](int currentSum, int index) {
            // Base cases
            if (currentSum == target) return 1;
            if (index == nums.size()) return 0;

            // Memoization check
            if (memo[currentSum].count(index)) return memo[currentSum][index];

            // Recursive DFS
            int skip = dfs(currentSum, index + 1); // Don't include the current number
            int include = 0;

            // Only include if the current number is not zero
            if (nums[index] != 0) {
                include = dfs(currentSum - 2 * nums[index], index + 1); // Convert + to -
            }

            // Store result in memo
            return memo[currentSum][index] = skip + include;
        };

        // Calculate the number of ways using the non-zero elements
        int ways = dfs(totalSum, 0);

        // Multiply by 2^zeroCount for the combinations of zeros
        return ways * (1 << zeroCount);  // 1 << zeroCount is equivalent to 2^zeroCount
    }
};

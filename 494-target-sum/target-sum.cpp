#include <vector>
#include <unordered_map>

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

        // Adjust target for negative indices
        int adjustedTarget = target + totalSum;
        if (adjustedTarget % 2 != 0) return 0; // Target must be even for split

        int halfTarget = adjustedTarget / 2;
        int n = nums.size();
        std::vector<int> dp(halfTarget + 1, 0);
        dp[0] = 1; // One way to make sum 0 (using no elements)

        // Dynamic Programming to count ways to reach halfTarget
        for (int num : nums) {
            if (num != 0) { // Only process non-zero elements
                for (int j = halfTarget; j >= num; --j) {
                    dp[j] += dp[j - num];
                }
            }
        }

        // Multiply by 2^zeroCount for the combinations of zeros
        return dp[halfTarget] * (1 << zeroCount);  // 1 << zeroCount is equivalent to 2^zeroCount
    }
};

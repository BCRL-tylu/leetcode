import java.util.*;

class Solution {
    private static final int MOD = 1000000007;

    public int sumOfGoodSubsequences(int[] nums) {
        // Find the maximum element in the nums array
        int mx = Arrays.stream(nums).max().getAsInt();
        
        // Create arrays to hold the counts and sums
        long[] count = new long[mx + 2];
        long[] sum = new long[mx + 2];
        long ans = 0;

        for (int num : nums) {
            // Calculate the total count of good subsequences ending with num
            long ttCount = (num - 1 >= 0 ? count[num - 1] : 0) + count[num + 1];
            // Include the number itself as a subsequence
            ttCount = (ttCount + 1) % MOD;

            // Calculate the total sum of good subsequences ending with num
            long ttSum = (num - 1 >= 0 ? sum[num - 1] : 0) + sum[num + 1];
            ttSum = (ttSum % MOD + ttCount * num % MOD) % MOD;

            // Update count and sum for the current number
            count[num] = (count[num] + ttCount) % MOD;
            sum[num] = (sum[num] + ttSum) % MOD;
        }

        // Calculate the total sum of all good subsequences
        for (long u : sum) {
            ans = (ans + u) % MOD;
        }

        return (int) ans;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        int[] nums = {1, 2, 1};
        int result = solution.sumOfGoodSubsequences(nums);
        System.out.println(result);  // Expected output: 14
    }
}

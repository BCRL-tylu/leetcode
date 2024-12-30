class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        const int MOD = 1e9 + 7; // Define the modulo constant
        
        // Use a vector for DP to count the number of good strings of length `i`
        std::vector<int> dp(high + 1, 0);
        dp[0] = 1; // Base case: 1 way to construct an empty string
        
        // Iterate through all possible lengths
        for (int i = 0; i <= high; ++i) {
            if (dp[i] == 0) continue; // Skip lengths that are unreachable
            if (i + zero <= high) {
                dp[i + zero] = (dp[i + zero] + dp[i]) % MOD;
            }
            if (i + one <= high) {
                dp[i + one] = (dp[i + one] + dp[i]) % MOD;
            }
        }

        // Sum up the counts of good strings within the range [low, high]
        int ans = 0;
        for (int i = low; i <= high; ++i) {
            ans = (ans + dp[i]) % MOD;
        }
        return ans;
    }
};

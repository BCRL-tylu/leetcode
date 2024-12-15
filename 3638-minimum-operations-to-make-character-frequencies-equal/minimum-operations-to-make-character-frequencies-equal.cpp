class Solution {
public:
    int makeStringGood(string s) {
        // Initialize a count array for each character in the alphabet
        int cnt[26] = {0};
        
        // Count the frequency of each character in the string
        for (char c : s) cnt[c - 'a']++;
        
        // Define the range of n (substrings' length) from 1 to the length of the string
        int l = 1;
        int r = s.length();
        
        // Initialize the result with a large value, as we are looking for a minimum
        int res = INT_MAX;

        // Loop through all possible lengths of substrings (from 1 to n)
        for (int n = l; n <= r; n++) {
            // dp[i][j] stores the minimum number of changes required for the first i letters of the alphabet
            // j = 0: when the character is not included in the substring of length n
            // j = 1: when the character is included in the substring of length n
            int dp[27][2] = {0};  // dp for 26 letters + extra index for base case
            // cy[i][j] stores the number of characters that have been used in the conversion
            int cy[27][2] = {0};
            
            // Loop through all characters of the alphabet (0 to 25 for 'a' to 'z')
            for (int i = 0; i < 26; i++) {
                // For the case where the character is not included in the substring of length n
                dp[i + 1][0] = min(dp[i][0], dp[i][1]) + cnt[i];
                cy[i + 1][0] = cnt[i];
                
                // If the current character's frequency is greater than or equal to n, it can be included
                if (cnt[i] >= n) {
                    dp[i + 1][1] = min(dp[i][0], dp[i][1]) + cnt[i] - n;
                    cy[i + 1][1] = cnt[i] - n;
                } else {
                    // If the current character's frequency is less than n, we have to make up for the deficit
                    dp[i + 1][1] = min(
                        dp[i][0] + max(0, n - cnt[i] - cy[i][0]), // Case where we take from the previous non-included state
                        dp[i][1] + max(0, n - cnt[i] - cy[i][1])  // Case where we take from the previous included state
                    );
                    cy[i + 1][1] = 0;  // Reset the cycle count for this state
                }
            }
            
            // Update the result with the minimum number of changes needed for the current substring length n
            res = min(res, min(dp[26][0], dp[26][1]));
        }

        // Return the final result, which is the minimum number of changes required
        return res;
    }
};
class Solution {
private:
    int transformCost(char a, char b) {
        int diff = abs(a - b);
        return min(diff, 26 - diff);
    }

public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        // dp[i][j] is a vector of length k+1 representing the best length using
        // exactly that many ops.
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(n, vector<int>(k + 1, 0)));

        // Base: single characters are palindromes of length 1.
        for (int i = 0; i < n; i++) {
            for (int op = 0; op <= k; op++) {
                dp[i][i][op] = 1;
            }
        }

        // Process substrings of length 2 to n.
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    for (int op = 0; op <= k; op++) {
                        dp[i][j][op] = dp[i + 1][j - 1][op] + 2;
                    }
                } else {
                    // First, update using non-pairing options.
                    for (int op = 0; op <= k; op++) {
                        dp[i][j][op] = max(dp[i + 1][j][op], dp[i][j - 1][op]);
                    }
                    // Then try pairing s[i] and s[j].
                    int cost = transformCost(s[i], s[j]);
                    for (int op = 0; op <= k - cost; op++) {
                        dp[i][j][op + cost] =
                            max(dp[i][j][op + cost], dp[i + 1][j - 1][op] + 2);
                    }
                }
            }
        }

        int ans = 0;
        for (int op = 0; op <= k; op++) {
            ans = max(ans, dp[0][n - 1][op]);
        }
        return ans;
    }
};
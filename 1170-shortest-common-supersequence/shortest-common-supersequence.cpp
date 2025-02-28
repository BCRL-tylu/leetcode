class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n1 = str1.size(), n2 = str2.size();
        // Build DP table for LCS
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, 0));
        for (int i = n1 - 1; i >= 0; i--) {
            for (int j = n2 - 1; j >= 0; j--) {
                if (str1[i] == str2[j])
                    dp[i][j] = dp[i+1][j+1] + 1;
                else
                    dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
        
        // Reconstruct the shortest common supersequence using the dp table.
        int i = 0, j = 0;
        string res;
        while(i < n1 && j < n2) {
            // If the characters match, add the character and move both pointers.
            if (str1[i] == str2[j]) {
                res.push_back(str1[i]);
                i++; j++;
            } 
            // Otherwise, move in the direction of the larger LCS.
            else if (dp[i+1][j] >= dp[i][j+1]) { // LCS in str1 larger than str2
                res.push_back(str1[i]);
                i++;
            } else {
                res.push_back(str2[j]);
                j++;
            }
        }
        // Append any leftover characters.
        while(i < n1) {
            res.push_back(str1[i]);
            i++;
        }
        while(j < n2) {
            res.push_back(str2[j]);
            j++;
        }
        return res;
    }
};

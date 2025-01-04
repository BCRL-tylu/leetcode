class Solution {
public:
    int countPalindromicSubsequence(string s) {
        // Use a 2D boolean array instead of an int matrix for memory efficiency
        std::vector<std::vector<bool>> matrix(26, std::vector<bool>(26, false));
        std::vector<int> firstPos(26, -1);
        std::vector<int> lastPos(26, -1);
        int ans = 0;

        // Step 1: Record the first and last positions of each character
        for (int i = 0; i < s.size(); ++i) {
            int current = s[i] - 'a';
            if (firstPos[current] == -1) {
                firstPos[current] = i;
            }
            lastPos[current] = i;
        }

        // Step 2: Check for palindromes
        for (int i = 0; i < 26; ++i) {
            if (firstPos[i] != -1 && lastPos[i] > firstPos[i]) {
                // Use a set to track unique characters between first and last positions
                std::vector<bool> seen(26, false);
                for (int j = firstPos[i] + 1; j < lastPos[i]; ++j) {
                    int midChar = s[j] - 'a';
                    if (!seen[midChar]) {
                        seen[midChar] = true;
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};

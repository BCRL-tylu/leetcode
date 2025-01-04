#include <unordered_set>
#include <vector>
#include <string>

class Solution {
public:
    int countPalindromicSubsequence(const std::string& s) {
        std::vector<int> firstPos(26, -1), lastPos(26, -1);
        int ans = 0;

        // Step 1: Record the first and last positions of each character
        for (int i = 0; i < s.size(); ++i) {
            int current = s[i] - 'a';
            if (firstPos[current] == -1) {
                firstPos[current] = i;
            }
            lastPos[current] = i;
        }

        // Step 2: Count unique palindromes for each character as the outer pair
        for (int i = 0; i < 26; ++i) {
            if (firstPos[i] != -1 && lastPos[i] > firstPos[i]) {
                // Use an unordered_set to track unique middle characters
                std::unordered_set<char> middleChars;
                for (int j = firstPos[i] + 1; j < lastPos[i]; ++j) {
                    middleChars.insert(s[j]);
                }
                ans += middleChars.size();
            }
        }

        return ans;
    }
};

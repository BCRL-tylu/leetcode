#include <string>
#include <algorithm>

class Solution {
public:
    std::string answerString(std::string w, int f) {
        char maxCh = 'a';
        int n = w.size();
        if (f == 1) return w;

        int k = n - f + 1;

        // Find the maximum character in the word
        for (char c : w) {
            maxCh = std::max(maxCh, c);
        }

        std::string maxStr = "";
        int startIdx = 0;

        // Traverse the string to find substrings starting with maxCh
        for (int i = 0; i < n; i++) {
            if (w[i] == maxCh) {
                int j = i + 1;
                int len = 1;

                // Efficiently append characters without constructing the string
                while (j < n && len < k && (w[j] != maxCh || w[j - 1] == maxCh)) {
                    len++;
                    j++;
                }

                // Compare character by character to avoid creating temp strings
                bool isBetter = false;
                for (int p = 0; p < len; p++) {
                    if (i + p >= n || startIdx + p >= n) break;
                    if (w[i + p] != w[startIdx + p]) {
                        isBetter = w[i + p] > w[startIdx + p];
                        break;
                    }
                }

                if (isBetter || maxStr.empty()) {
                    maxStr = w.substr(i, len);
                    startIdx = i;
                }
            }
        }

        int sz = maxStr.size();
        std::string tempAdd = w.substr(startIdx + sz, std::min(k - sz, n - (startIdx + sz)));
        return maxStr + tempAdd;
    }
};

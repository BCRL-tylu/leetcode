#include <string>
#include <algorithm>

class Solution {
public:
    string answerString(string w, int f) {
        char maxCh = 'a'; // Renamed to maxCh
        int n = w.size();
        if (f == 1) return w;

        int k = n - f + 1;
        string ans = "";

        // Find the maximum character in the word
        for (char c : w) {
            maxCh = max(maxCh, c); // Updated variable name
        }

        string maxStr = "";  // To keep track of the largest substring
        int startIdx = 0;         // To track the starting index of the max substring

        // Traverse the string to find substrings starting with maxCh
        for (int i = 0; i < n; i++) {
            if (w[i] == maxCh) {
                string tempAns = "";
                tempAns += maxCh; // Updated variable name
                // keep appending elements until reach string length limit or/reach word's boundry or/ meet another maximum char (unless consecutively with starting maxCh)
                while (i + 1 < n && tempAns.size() < min(k, n - i) && (w[i + 1] != maxCh || tempAns.back() == maxCh)) {
                    tempAns += w[++i];
                }

                // Compare tempAns with current largest substring
                if (tempAns > maxStr) {
                    maxStr = tempAns; // Update the largest substring
                    startIdx = i;     // Update the index of the largest substring
                }
            }
        }

        int sz = maxStr.size();
        string tempAdd = w.substr(startIdx + 1, min(k - sz, n - startIdx));
        ans = maxStr + tempAdd; // Combine the largest substring with the additional characters
        return ans; // Return the result trimmed to size k
    }
};

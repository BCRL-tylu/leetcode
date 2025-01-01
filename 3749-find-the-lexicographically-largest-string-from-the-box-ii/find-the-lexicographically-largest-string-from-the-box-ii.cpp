#include <string>
#include <algorithm>

class Solution {
public:
    string answerString(string word, int f) {
        if (f == 1) return word;

        char mc = 'a'; // Maximum character in the word
        int len = word.size();
        int sl = len - f + 1; // Length of the longest substring to be formed
        string res = "";

        // Find the maximum character in the word
        for (char ch : word) {
            mc = max(mc, ch);
        }

        string ls = "";  // Largest substring
        int lse = 0;     // Ending index of the largest substring

        // Traverse the string to find substrings starting with mc
        for (int i = 0; i < len; i++) {
            if (word[i] == mc) {
                string cs = ""; // Current substring
                cs += mc;

                // Compare characters while building `cs`
                int lsPos = 1; // Position in the current `ls` to compare
                while (cs.size() < min(sl, len - i) && (word[i + 1] != mc || cs.back() == mc) && i + 1 < len) {
                    char nextChar = word[++i];
                    cs += nextChar;

                    // Compare the current `cs` character with the corresponding `ls` character
                    if (lsPos < ls.size() && nextChar < ls[lsPos]) {
                        break; // Stop if the current substring can't be better
                    }
                    if (lsPos < ls.size() && nextChar > ls[lsPos]) {
                        ls.clear(); // Invalidate `ls` since `cs` is better
                    }
                    lsPos++;
                }

                // Update `ls` and `lse` if `cs` is better
                if (ls.empty() || cs.size() > ls.size()) {
                    ls = cs;
                    lse = i;
                }
            }
        }

        int lss = ls.size(); // Largest substring size
        // Construct the remaining substring
        string rem = word.substr(lse + 1, min(sl - lss, len - lse));
        res = ls + rem;

        return res;
    }
};

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
                 // Keep appending elements until we reach the limit
                // Stop when reaching the boundary of the word, the substring limit, or encountering another mc not connected consecutively
                int mlength = min(sl, len - i);
                while (cs.size() < mlength && (word[i + 1] != mc || cs.back() == mc)) {
                    char nextChar = word[++i];
                    bool rs = lsPos < ls.size();
                    // Compare the current `cs` character with the corresponding `ls` character
                    if (rs && nextChar < ls[lsPos]) {
                        break; // Stop if the current substring can't be better
                    }else if (rs && nextChar > ls[lsPos]) {
                        ls.clear(); // Invalidate `ls` since `cs` is better
                    }
                    cs += nextChar;
                    lsPos++;
                }

                if (ls.empty() || cs.size() > ls.size()) {
                    ls = cs;
                    lse = i;
                }
            }
        }

        int lss = ls.size(); 
        string rem = word.substr(lse + 1, min(sl - lss, len - lse));
        res = ls + rem;

        return res;
    }
};
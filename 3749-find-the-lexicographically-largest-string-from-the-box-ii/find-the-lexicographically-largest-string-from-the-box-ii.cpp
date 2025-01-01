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

                // Keep appending elements until we reach the limit
                // Stop when reaching the boundary of the word, the substring limit, or encountering another mc not connected consecutively
                while (i + 1 < len && cs.size() < min(sl, len - i) && (word[i + 1] != mc || cs.back() == mc)) {
                    cs += word[++i];
                }

                // Update the largest substring if the current one is better
                if (cs > ls) {
                    ls = cs;
                    lse = i;
                }
            }
        }

        int lss = ls.size(); // Largest substring size
        // Return the result trimmed to the desired size
        string rem = word.substr(lse + 1, min(sl - lss, len - lse));
        res = ls + rem;

        return res; 
    }
};
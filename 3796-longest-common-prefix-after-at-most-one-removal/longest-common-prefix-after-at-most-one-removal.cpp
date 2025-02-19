//@bcrl-tylu
class Solution {
public:
    // Returns the length of the prefix of s that matches t,
    // where we are allowed to skip one character in t.
    int longestCommonPrefix(const string &s, const string &t) {
        int i = 0, j = 0;
        bool skipped = false;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                ++i;
                ++j;
            } else if (!skipped) {
                // Skip one character in t.
                skipped = true;
                ++i;
            } else {
                break;
            }
        }
        return i-skipped;
    }
};
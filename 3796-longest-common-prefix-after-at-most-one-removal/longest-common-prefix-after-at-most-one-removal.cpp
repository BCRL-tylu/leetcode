class Solution {
public:
    int longestCommonPrefix(string s, string t) {
        int i = 0, d = 0;
        for (; i < s.length() && i - d < t.length(); ++i) {
            if (s[i] != t[i - d]) {
                if (d == 1) break;
                d = 1;
            }
        }
        return i - d;
    }
};
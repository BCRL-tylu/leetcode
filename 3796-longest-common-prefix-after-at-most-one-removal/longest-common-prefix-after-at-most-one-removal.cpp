class Solution {
public:
    int longestCommonPrefix(string s, string t) {
        int j = 0, i = 0;
        for (; i < s.size() && j < t.size() && i - j < 2; ++i)
            j += s[i] == t[j];
        return j;
    }
};
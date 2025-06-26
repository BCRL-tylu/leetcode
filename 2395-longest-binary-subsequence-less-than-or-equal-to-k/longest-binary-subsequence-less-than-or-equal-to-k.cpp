class Solution {
public:
    int longestSubsequence(string s, int k) {
        long long val = 0;  
        int res = 0;         
        for (int i = (int)s.size() - 1; i >= 0; --i) {
            if (s[i] == '0') {
                ++res;
            }
            else {
                if (res < 63 && val + (1LL << res) <= k) {
                    val += (1LL << res);
                    ++res;
                }
            }
        }

        return res;
    }
};

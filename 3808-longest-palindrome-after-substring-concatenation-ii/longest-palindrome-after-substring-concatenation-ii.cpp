class Solution {
public:
    int longestPalindrome(string s, string t) {
        // Check if s and t are composed entirely of the same character
        if (!s.empty() && !t.empty() && 
            all_of(s.begin(), s.end(), [&](char c){ return c == s[0]; }) &&
            all_of(t.begin(), t.end(), [&](char c){ return c == t[0]; }) &&
            s[0] == t[0]) {
            return s.size() + t.size();
        }
        
        // ... (otherwise use your DP-based solution)
        int n = s.size(), m = t.size();
        int ans = 0;
        
        // Precompute longest palindromic substrings in s
        vector<vector<bool>> dpS(n, vector<bool>(n, false));
        vector<int> LPS_start(n, 1);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if(s[i] == s[j] && (j - i < 2 || dpS[i+1][j-1])){
                    dpS[i][j] = true;
                    LPS_start[i] = max(LPS_start[i], j - i + 1);
                    ans = max(ans, j - i + 1);
                }
            }
        }
        
        // Precompute longest palindromic substrings in t
        vector<vector<bool>> dpT(m, vector<bool>(m, false));
        vector<int> LPS_end(m, 1);
        for (int i = m - 1; i >= 0; i--) {
            for (int j = i; j < m; j++) {
                if(t[i] == t[j] && (j - i < 2 || dpT[i+1][j-1])){
                    dpT[i][j] = true;
                    LPS_end[j] = max(LPS_end[j], j - i + 1);
                    ans = max(ans, j - i + 1);
                }
            }
        }
        
        // Check cross-palindromes: one substring from s and one from t.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if(s[i] == t[j]) {
                    int match = 0;
                    while(i + match < n && j - match >= 0 && s[i + match] == t[j - match]) {
                        match++;
                        ans = max(ans, 2 * match);
                        if(i + match < n) {
                            ans = max(ans, 2 * match + LPS_start[i + match]);
                        }
                        if(j - match >= 0) {
                            ans = max(ans, 2 * match + LPS_end[j - match]);
                        }
                    }
                }
            }
        }
        
        return ans;
    }
};

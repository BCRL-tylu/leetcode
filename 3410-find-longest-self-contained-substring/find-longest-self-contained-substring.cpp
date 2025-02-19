
class Solution {
public:
    int maxSubstringLength(string s) {
        // greedy
        vector<int> l(26, INT_MAX), r(26, -1), c(26, 0);
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int id = s[i] - 'a';
            l[id] = min(l[id], i);
            r[id] = max(r[id], i);
        }
        int ans = -1;
        for (int i = 0; i < 26; i++) {
            if (l[i] == INT_MAX)
                continue;
            int m = l[i], v = r[s[m] - 'a'];
            bool updated = true;
            for (int t = m; t < n; t++) {
                char ct = s[t] - 'a';
                if (l[ct] < m) {
                    updated = false;
                    break;
                }
                v = max(v, r[ct]);
                if (v == t && !(m == 0 && v == n - 1)) {
                    ans = max(ans, v - m + 1);
                }
            }
        }
        return ans;
    }
};
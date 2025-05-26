#include <string>
#include <cstring>
using namespace std;

class Solution {
    static const int MAXN = 255;
    bool can[MAXN][MAXN];
    string dp[MAXN][MAXN];

    inline bool consecutive(char a, char b) {
        return (a == 'a' && b == 'z') || (a == 'z' && b == 'a') || (a + 1 == b) || (b + 1 == a);
    }

public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        if (n <= 1) return s;

        // Initialize
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                can[i][j] = false;
                dp[i][j].clear();
            }
        }

        // DP for full removability parity-based
        for (int len = 2; len <= n; ++len) {
            if (len & 1) continue;
            for (int l = 0; l + len <= n; ++l) {
                int r = l + len - 1;
                for (int k = l + 1; k <= r; ++k) {
                    if (consecutive(s[l], s[k])) {
                        bool mid   = (k == l + 1) || can[l + 1][k - 1];
                        bool right = (k == r)     || can[k + 1][r];
                        if (mid && right) {
                            can[l][r] = true;
                            break;
                        }
                    }
                }
            }
        }

        // DP for result with early exit on empty
        for (int len = 1; len <= n; ++len) {
            for (int l = 0; l + len <= n; ++l) {
                int r = l + len - 1;
                // Keep s[l]
                string best;
                best.reserve(len);
                best.push_back(s[l]);
                if (l + 1 <= r) best += dp[l + 1][r];

                // Try removable prefixes; break early if empty achieved
                for (int i = l + 1; i <= r; ++i) {
                    if (can[l][i]) {
                        const string &cand = (i + 1 <= r ? dp[i + 1][r] : string());
                        if (cand < best) {
                            best = cand;
                            if (best.empty()) break;
                        }
                    }
                }
                dp[l][r].swap(best);
            }
        }
        return dp[0][n - 1];
    }
};

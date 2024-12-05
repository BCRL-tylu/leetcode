typedef uint64_t u64;
constexpr u64 mod = 1e9 + 7;
constexpr u64 n = 800;

constexpr auto dp = [] {
    array<u64, n + 1> dp{};
    for (u64 i = 2; i <= n; i++) {
        dp[i] = dp[__builtin_popcount(i)] + 1;
    }
    return dp;
}();

auto C = [] {
    array<array<u64, n + 1>, n + 1> C{};
    C[0][0] = C[1][0] = C[1][1] = 1;
    for (u64 i = 2; i <= n; i++) {
        C[i][0] = 1;
        for (u64 j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            C[i][j] %= mod;
        }
    }
    return C;
}();

class Solution {
public:
    u64 countKReducibleNumbers(string s, u64 k) {
        u64 n = s.size();
        u64 c1 = 0;
        u64 ans = 0;
        for (u64 i = 0; i < n; i++) {
            if (s[i] == '1') {
                for (u64 c2 = 0; i + c2 < n; c2++) {
                    if (c1 + c2 > 0 && dp[c1 + c2] + 1 <= k) {
                        ans += C[n - i - 1][c2];
                        ans %= mod;
                    }
                }
                c1++;
            }
        }
        return ans;
    }
};
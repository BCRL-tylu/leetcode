static const int MOD = 1000000007;

inline int add(int a, int b) { a += b; if (a >= MOD) a -= MOD; return a; }
inline int mul(long long a, long long b) { return int((a * b) % MOD); }

int modexp(long long base, int exp) {
    long long res = 1;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return int(res);
}
class Solution {
public:
    int magicalSum(int m, int k, vector<int>& nums) {
    int n = nums.size();
    vector<int> fact(m+1, 1), inv_fact(m+1, 1);
    for (int i = 1; i <= m; ++i) fact[i] = mul(fact[i-1], i);
    inv_fact[m] = modexp(fact[m], MOD-2);
    for (int i = m; i > 0; --i) inv_fact[i-1] = mul(inv_fact[i], i);

    // Precompute power of nums[i]^c for c=0..m
    vector<vector<int>> pow_nums(n, vector<int>(m+1, 1));
    for (int i = 0; i < n; ++i) {
        for (int c = 1; c <= m; ++c) {
            pow_nums[i][c] = mul(pow_nums[i][c-1], nums[i]);
        }
    }

    // We'll process up to n + log2(m) + 2 bits
    int B = n + 7;
    // dp[cur][u][b][s]
    int cur = 0, nxt = 1;
    static int dp[2][51][51][51];
    memset(dp, 0, sizeof(dp));
    dp[cur][0][0][0] = 1;

    for (int i = 0; i < B; ++i) {
        memset(dp[nxt], 0, sizeof(dp[nxt]));
        for (int u = 0; u <= m; ++u) {
            for (int b = 0; b <= m; ++b) {
                for (int s = 0; s <= m; ++s) {
                    int val = dp[cur][u][b][s];
                    if (!val) continue;
                    if (i < n) {
                        // try picking index i c times
                        for (int c = 0; c + s <= m; ++c) {
                            int tot = u + c;
                            int bit = tot & 1;
                            int u2 = tot >> 1;
                            int b2 = b + bit;
                            int s2 = s + c;
                            int coeff = mul(pow_nums[i][c], inv_fact[c]);
                            dp[nxt][u2][b2][s2] = add(
                                dp[nxt][u2][b2][s2], mul(val, coeff)
                            );
                        }
                    } else {
                        // no more picks allowed, c=0
                        int tot = u;
                        int bit = tot & 1;
                        int u2 = tot >> 1;
                        int b2 = b + bit;
                        dp[nxt][u2][b2][s] = add(dp[nxt][u2][b2][s], val);
                    }
                }
            }
        }
        swap(cur, nxt);
    }

    int result = dp[cur][0][k][m];
    result = mul(result, fact[m]);
    return result;
    }
};
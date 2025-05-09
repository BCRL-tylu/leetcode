#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

// fast exponentiation modulo MOD
long long mod_pow(long long a, long long e = MOD - 2) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

class Solution {
public:
    int countBalancedPermutations(string num) {
        int n = num.size();
        vector<int> cnt(10, 0);
        int total_sum = 0;
        for (char c : num) {
            int d = c - '0';
            cnt[d]++;
            total_sum += d;
        }
        // If total sum is odd, no balanced arrangement exists
        if (total_sum % 2 != 0) return 0;
        int target = total_sum / 2;
        int ne = (n + 1) / 2;  // number of even indices (0-based)
        int no = n / 2;        // number of odd indices

        // Precompute factorials and inverse factorials up to n
        vector<long long> fact(n + 1, 1), invf(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invf[n] = mod_pow(fact[n]);
        for (int i = n; i > 0; i--) {
            invf[i - 1] = invf[i] * i % MOD;
        }

        // dp[c][s] = sum of products of inverse factorials for choosing c digits summing to s
        vector<vector<long long>> dp(ne + 1, vector<long long>(target + 1, 0));
        dp[0][0] = 1;

        // Process each digit 0..9
        for (int d = 0; d <= 9; d++) {
            int c = cnt[d];
            vector<vector<long long>> next_dp(ne + 1, vector<long long>(target + 1, 0));
            for (int used = 0; used <= ne; used++) {
                for (int sum = 0; sum <= target; sum++) {
                    if (!dp[used][sum]) continue;
                    long long cur = dp[used][sum];
                    // try putting k copies of digit d in even positions
                    for (int k = 0; k <= c; k++) {
                        int nu = used + k;
                        int ns = sum + k * d;
                        if (nu > ne || ns > target) break;
                        long long ways = cur * invf[k] % MOD * invf[c - k] % MOD;
                        next_dp[nu][ns] = (next_dp[nu][ns] + ways) % MOD;
                    }
                }
            }
            dp.swap(next_dp);
        }

        long long ways = dp[ne][target];
        long long result = ways * fact[ne] % MOD * fact[no] % MOD;
        return int(result);
    }
};

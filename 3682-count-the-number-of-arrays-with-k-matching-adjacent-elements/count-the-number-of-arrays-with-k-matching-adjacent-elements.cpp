#include <vector>

using namespace std;

class Combination {
private:
    vector<long long> fac, inv;
    long long MOD;

    long long modpow(long long n, long long x, long long MOD) {
        if (x < 0) {
            return modpow(modpow(n, -x, MOD), MOD - 2, MOD);
        }
        n %= MOD;
        long long res = 1;
        while (x) {
            if (x & 1) {
                res = res * n % MOD;
            }
            n = n * n % MOD;
            x >>= 1;
        }
        return res;
    }

public:
    Combination(long long maxN, long long mod) : MOD(mod) {
        fac.resize(maxN + 1);
        inv.resize(maxN + 1);
        fac[0] = 1;

        for (long long i = 1; i <= maxN; ++i) {
            fac[i] = fac[i - 1] * i % MOD;
        }

        inv[maxN] = modpow(fac[maxN], MOD - 2, MOD);
        for (long long i = maxN - 1; i >= 0; --i) {
            inv[i] = inv[i + 1] * (i + 1) % MOD;
        }
    }

    long long nCr(long long n, long long r) {
        if (n < r || n < 0 || r < 0) return 0;
        return fac[n] * inv[r] % MOD * inv[n - r] % MOD;
    }

    long long power(long long base, long long exp) {
        return modpow(base, exp, MOD); // Public method for modular exponentiation
    }
};

constexpr long long MOD = 1e9 + 7;

class Solution {
private:
    Combination comb;

public:
    Solution() : comb(1e5, MOD) {} // Initialize combination for up to 100000
    int countGoodArrays(int n, int m, int k) {
        long long arrangementWays = m * comb.power(m - 1, n - 1 - k) % MOD; // Use public method
        long long combinationWays = comb.nCr(n - 1, n - 1 - k);
        return (arrangementWays * combinationWays) % MOD; // Final result
    }
};


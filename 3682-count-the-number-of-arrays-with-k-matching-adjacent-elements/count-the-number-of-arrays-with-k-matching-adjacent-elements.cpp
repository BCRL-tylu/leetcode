class Solution {
    static constexpr long long MOD = 1'000'000'007LL;

    /* fast a^e mod MOD */
    static long long modPow(long long a, long long e) {
        long long res = 1;
        a %= MOD;
        while (e) {
            if (e & 1) res = res * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return res;
    }

public:
    int countGoodArrays(int n, int m, int k) {
        /* invalid parameter ranges */
        if (k < 0 || k > n - 1) return 0;

        long long breaks = n - k - 1;          // b = n‑k‑1
        if (breaks < 0) return 0;

        /* factorials up to n‑1 (fits easily in memory for usual constraints) */
        std::vector<long long> fact(n), invFact(n);
        fact[0] = 1;
        for (int i = 1; i < n; ++i) fact[i] = fact[i - 1] * i % MOD;
        invFact[n - 1] = modPow(fact[n - 1], MOD - 2);   // Fermat inverse
        for (int i = n - 1; i > 0; --i)
            invFact[i - 1] = invFact[i] * i % MOD;

        /* C(n‑1, breaks) */
        long long choose =
            fact[n - 1] * invFact[breaks] % MOD * invFact[n - 1 - breaks] % MOD;

        /* m * (m‑1)^{breaks} */
        long long ways =
            (static_cast<long long>(m) % MOD) *
            modPow((m - 1 + MOD) % MOD, breaks) % MOD;

        return static_cast<int>(choose * ways % MOD);
    }
};

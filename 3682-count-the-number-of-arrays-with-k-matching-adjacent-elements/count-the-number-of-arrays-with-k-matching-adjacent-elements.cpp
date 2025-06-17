const int MOD = 1e9 + 7;
const int MX  = 100000;              // make ≥ max n in the tests

long long fact[MX + 1];
long long inv_fact[MX + 1];

class Solution {
    /* fast a^e (mod MOD) */
    long long qpow(long long a, long long e) {
        long long r = 1 % MOD;
        a %= MOD;
        while (e) {
            if (e & 1) r = r * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return r;
    }

    /* nCk (mod MOD), assumes 0 ≤ k ≤ n ≤ MX */
    long long comb(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
    }

    /* one‑time factorial table */
    void init() {
        if (fact[0]) return;                 // already done
        fact[0] = 1;
        for (int i = 1; i <= MX; ++i) fact[i] = fact[i - 1] * i % MOD;

        inv_fact[MX] = qpow(fact[MX], MOD - 2);      // Fermat inverse
        for (int i = MX; i; --i) inv_fact[i - 1] = inv_fact[i] * i % MOD;
    }

public:
    int countGoodArrays(int n, int m, int k) {
        init();

        /* impossible cases */
        if (k < 0 || k > n - 1) return 0;

        /* special case m = 1 : only one possible array (all 1s) */
        if (m == 1) return (k == n - 1 ? 1 : 0);

        int breaks = n - k - 1;                       // positions where value changes
        long long choose = comb(n - 1, breaks);       // C(n‑1, n‑k‑1)
        long long ways   = (long long)m % MOD *
                           qpow(m - 1, breaks) % MOD; // m·(m‑1)^{breaks}

        return (int)(choose * ways % MOD);
    }
};

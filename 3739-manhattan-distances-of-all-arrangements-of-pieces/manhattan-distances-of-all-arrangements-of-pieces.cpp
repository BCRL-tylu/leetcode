#include <vector>
using namespace std;

class Solution {
public:
    int distanceSum(int m, int n, int k) {
        const int MOD = 1000000007;
        int N = m * n;
        
        // Precompute factorials and inverse factorials up to N.
        vector<long long> fact, invFact;
        precomputeFactorials(N, fact, invFact, MOD);
        
        // Every unordered pair of cells appears in C(N-2, k-2) arrangements.
        long long comb = nCr(N - 2, k - 2, fact, invFact, MOD);
        
        // Sum the Manhattan distances contributed by differences in rows.
        long long rowSum = 0;
        for (int d = 1; d < m; d++) {
            rowSum = (rowSum + (long long)d * (m - d)) % MOD;
        }
        // Each pair of rows gives n^2 pairs of cells.
        long long part1 = ((long long)n * n % MOD) * rowSum % MOD;
        
        // Sum the Manhattan distances contributed by differences in columns.
        long long colSum = 0;
        for (int d = 1; d < n; d++) {
            colSum = (colSum + (long long)d * (n - d)) % MOD;
        }
        // Each pair of columns gives m^2 pairs of cells.
        long long part2 = ((long long)m * m % MOD) * colSum % MOD;
        
        // Total sum of Manhattan distances over all unordered pairs of cells.
        long long S = (part1 + part2) % MOD;
        
        // Multiply S by the combination factor.
        long long ans = (comb * S) % MOD;
        return (int)ans;
    }
    
private:
    // Modular exponentiation.
    long long modExp(long long base, long long exp, int mod) {
        long long res = 1;
        while(exp > 0) {
            if(exp & 1)
                res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }
    
    // Precompute factorials and inverse factorials modulo mod.
    void precomputeFactorials(int maxN, vector<long long>& fact, vector<long long>& invFact, int mod) {
        fact.resize(maxN + 1);
        invFact.resize(maxN + 1);
        fact[0] = 1;
        for (int i = 1; i <= maxN; i++) {
            fact[i] = fact[i - 1] * i % mod;
        }
        invFact[maxN] = modExp(fact[maxN], mod - 2, mod);
        for (int i = maxN - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % mod;
        }
    }
    
    // Compute nCr modulo mod using precomputed factorials.
    long long nCr(int n, int r, const vector<long long>& fact, const vector<long long>& invFact, int mod) {
        if (r < 0 || r > n) return 0;
        return ((fact[n] * invFact[r]) % mod * invFact[n - r]) % mod;
    }
};

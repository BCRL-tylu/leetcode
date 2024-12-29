#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    vector<long long> factorial;
    vector<long long> inverseFactorial;

    // Precompute factorials and inverse factorials
    void precomputeFactorials(int maxN, int mod) {
        factorial.resize(maxN + 1);
        inverseFactorial.resize(maxN + 1);
        factorial[0] = 1;

        for (int i = 1; i <= maxN; i++) {
            factorial[i] = (factorial[i - 1] * i) % mod;
        }

        inverseFactorial[maxN] = modInverse(factorial[maxN], mod);
        for (int i = maxN - 1; i >= 0; i--) {
            inverseFactorial[i] = (inverseFactorial[i + 1] * (i + 1)) % mod;
        }
    }

    // Function to calculate nCr % mod
    long long nCr(int n, int r, int mod) {
        if (r > n || n < 0 || r < 0) return 0;
        return (factorial[n] * inverseFactorial[r] % mod * inverseFactorial[n - r] % mod) % mod;
    }

    // Function to calculate modular inverse using Fermat's Little Theorem
    long long modInverse(long long a, int mod) {
        long long m = mod - 2; // mod is prime
        long long res = 1;
        long long x = a;

        while (m > 0) {
            if (m % 2 == 1) {
                res = (res * x) % mod;
            }
            x = (x * x) % mod;
            m /= 2;
        }
        return res;
    }

    // Function to calculate total conformations
    long long totalConformations(int k, int m, int l, int mod) {
        if (k < 2 * m) return 0; // Not enough length for valid segments
        long long splittingWays = nCr(k - m - 1, m - 1, mod); // Ways to split
        long long arrangementWays = nCr(m + l, l, mod);       // Ways to insert identical segments

        // Calculate total ways using modulo
        long long totalWays = (splittingWays * arrangementWays) % mod;

        if (splittingWays == 0 && k == 0) {
            return arrangementWays;
        }
        return totalWays;
    }

    // Modular exponentiation
    long long modPow(int base, int exponent, int mod) {
        long long result = 1;
        long long b = base;  // Use long long to avoid overflow

        while (exponent > 0) {
            if (exponent % 2 == 1) {  // If exponent is odd
                result = (result * b) % mod;
            }
            b = (b * b) % mod;  // Square the base
            exponent /= 2;      // Divide exponent by 2
        }
        return result;
    }

public:
    int countGoodArrays(int n, int m, int k) {
        int mod = 1e9 + 7;
        int iter = n - k;
        int ans = 0;

        // Precompute factorials up to n
        precomputeFactorials(n, mod);

        // Use modular exponentiation
        long long combination = (m * modPow(m - 1, iter - 1, mod)) % mod;

        for (int i = 0; i <= iter; i++) {
            int nc = iter - i;
            if (nc > (n - i) / 2) {
                continue;
            }
            ans = (ans + totalConformations(n - i, nc, i, mod) * combination % mod) % mod;
        }
        return ans;
    }
};

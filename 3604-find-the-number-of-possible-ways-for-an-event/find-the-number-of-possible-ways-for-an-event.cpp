#include <vector>
#include <iostream>

class Solution {
public:
    static std::vector<std::vector<long long>> comb; // To store computed combinations
    static const int MOD = 1000000007;

    // Default constructor (without parameters)
    Solution() {
        // Initialize comb with a size; you can choose an appropriate default value
        comb.resize(1001, std::vector<long long>(1001, -1)); // Default size of 100
    }

    // Constructor with maxX parameter
    Solution(int maxX) {
        // Resize and initialize the combination table with -1
        comb.resize(maxX + 1, std::vector<long long>(maxX + 1, -1));
    }

    long long combUtil(int n, int k) {
        if (k > n) return 0; // C(n, k) = 0 if k > n
        if (k == 0 || k == n) return 1; // C(n, 0) = C(n, n) = 1

        // Check if already computed
        if (comb[n][k] != -1) return comb[n][k];

        // Compute C(n, k) using the recursive relation
        comb[n][k] = (combUtil(n - 1, k - 1) + combUtil(n - 1, k)) % MOD;
        return comb[n][k];
    }

    long long modPow(long long base, long long exp) {
        long long result = 1;
        base %= MOD; // In case base is larger than MOD
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exp /= 2;
        }
        return result;
    }

    int numberOfWays(int n, int x, int y) {
        long long answer = 0;
        int range = std::min(n, x);
        
        for (int i = 1; i <= range; ++i) {
            long long cof1 = 0;
            for (int j = 0; j <= i; ++j) {
                long long sign = (j % 2 == 0) ? 1 : -1; // (-1)^j
                long long term = (combUtil(i, j) * modPow(i - j, n)) % MOD;
                cof1 = (cof1 + sign * term + MOD) % MOD; // Ensure non-negative
            }
            long long bandWays = (cof1 * combUtil(x, i)) % MOD; // Ways to choose bands
            long long scoreWays = modPow(y, i); // Ways to assign scores
            answer = (answer + bandWays * scoreWays) % MOD; // Total ways
        }

        return answer;
    }
};

// Initialize the combination vector
std::vector<std::vector<long long>> Solution::comb;

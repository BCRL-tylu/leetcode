#include <vector>
#include <iostream>
using namespace std;

const int MAX_N = 1000;
long long s[MAX_N + 1][MAX_N + 1], mod = 1e9 + 7;

// Initialize Stirling numbers of the second kind
//count the number of ways to partition a set of n labelled objects into k nonempty unlabelled subsets
auto init = [] {
    s[0][0] = 1;
    for (int i = 1; i <= MAX_N; i++) {
        for (int j = 1; j <= i; j++) {
            s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * j) % mod;
        }
    }
    return 0;
}();

class Solution {
public:
    int numberOfWays(int n, int x, int y) {
        long long res = 0, perm = 1, pow = 1;
        for (int i = 1; i <= min(n, x); i++) {
            // Calculate the number of ways to assign stages (permutations)
            perm = perm * (x - i + 1) % mod;
            // Calculate the number of ways to assign scores (powers)
            pow = pow * y % mod;
            // Accumulate the result using Stirling numbers
            res = (res + perm * s[n][i] % mod * pow) % mod;
        }
        return res;
    }
};
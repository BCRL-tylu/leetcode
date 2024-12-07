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
    int waysToDistribute(int n, int k) {
        return s[n][k];
    }
};
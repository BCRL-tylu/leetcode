#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    const long long MOD = 1e9 + 7;

    long long choose2(long long n) {
        if (n < 2) return 0;
        return (n * (n - 1) / 2) % MOD;
    }

    int subsequencesWithMiddleMode(vector<int>& a) {
        int n = a.size();
        long long res = 0;
        unordered_map<long long, long long> lmap, rmap;

        for (auto& x : a) {
            rmap[x]++;
        }

        long long P = 0, Q = 0, U = 0, V = 0, W = 0;
        // sum of squares for the number of different elements on right
        for (auto& [_, f] : rmap) {
            Q = (Q + (f * f) % MOD) % MOD;
        }

        for (int mid = 0; mid < n; mid++) {
            int x = a[mid];

            // Update the frequency maps
           // P = p - left[mode]^2

            // Q = Q - right[mode]^2
            Q = (Q - (rmap[x] * rmap[x]) % MOD + MOD) % MOD;
            // U = U - left[mode]*right[mode]
            U = (U - (lmap[x] * rmap[x]) % MOD + MOD) % MOD;
            // V = v - left[mode]^2*right[mode]
            V = (V - (lmap[x] * lmap[x] * rmap[x] % MOD) + MOD) % MOD;
            // w = W-left[mode]*right[mode]^2
            W = (W - (lmap[x] * rmap[x] * rmap[x] % MOD) + MOD) % MOD;

            // remove current mode from right map
            rmap[x]--;


            Q = (Q + (rmap[x] * rmap[x]) % MOD) % MOD;
            U = (U + (lmap[x] * rmap[x]) % MOD) % MOD;
            V = (V + (lmap[x] * lmap[x] % MOD * rmap[x] % MOD)) % MOD;
            W = (W + (lmap[x] * rmap[x] % MOD * rmap[x] % MOD)) % MOD;

            // Calculate left and right sizes
            int left = mid;
            int right = n - 1 - mid;
            // total ways of selecting arbiatry two from right and left
            res = (res + (choose2(left) * choose2(right)) % MOD) % MOD;

            res = (res - (choose2(left - lmap[x]) * choose2(right - rmap[x]) % MOD) + MOD) % MOD;

            // Adjust for the various cases
            int left1 = left - lmap[x];
            int right1 = right - rmap[x];
            long long P1 = (P - (lmap[x] * lmap[x]) % MOD + MOD) % MOD;
            long long Q1 = (Q - (rmap[x] * rmap[x]) % MOD + MOD) % MOD;
            long long U1 = (U - (lmap[x] * rmap[x]) % MOD + MOD) % MOD;
            long long V1 = (V - (lmap[x] * lmap[x] % MOD * rmap[x] % MOD) + MOD) % MOD;
            long long W1 = (W - (lmap[x] * rmap[x] % MOD * rmap[x] % MOD) + MOD) % MOD;

            res = (res - (P1 - left1 + MOD) % MOD * rmap[x] % MOD * right1 % MOD * modInverse(2) % MOD + MOD) % MOD;
            res = (res - (Q1 - right1 + MOD) % MOD * lmap[x] % MOD * left1 % MOD * modInverse(2) % MOD + MOD) % MOD;
            res = (res - U1 * (lmap[x] * right % MOD - 2 * lmap[x] * rmap[x] % MOD + rmap[x] * left % MOD + MOD) % MOD + MOD) % MOD;
            res = (res - V1 * -rmap[x] % MOD + MOD) % MOD;
            res = (res - W1 * -lmap[x] % MOD + MOD) % MOD;

            // Ensure the result remains non-negative
            res = (res + MOD) % MOD;

            // Update lmap
            P = (P - (lmap[x] * lmap[x]) % MOD + MOD) % MOD;
            Q = (Q - (rmap[x] * rmap[x]) % MOD + MOD) % MOD;
            U = (U - (lmap[x] * rmap[x]) % MOD + MOD) % MOD;
            V = (V - (lmap[x] * lmap[x] % MOD * rmap[x] % MOD) + MOD) % MOD;
            W = (W - (lmap[x] * rmap[x] % MOD * rmap[x] % MOD) + MOD) % MOD;

            lmap[x]++;
            P = (P + (lmap[x] * lmap[x]) % MOD) % MOD;
            Q = (Q + (rmap[x] * rmap[x]) % MOD) % MOD;
            U = (U + (lmap[x] * rmap[x]) % MOD) % MOD;
            V = (V + (lmap[x] * lmap[x] % MOD * rmap[x] % MOD)) % MOD;
            W = (W + (lmap[x] * rmap[x] % MOD * rmap[x] % MOD)) % MOD;
        }

        return res % MOD;
    }

private:
    long long modInverse(long long a) {
        long long m = MOD;
        long long m0 = m, y = 0, x = 1;

        if (m == 1) return 0;

        while (a > 1) {
            long long q = a / m;
            long long t = m;

            m = a % m;
            a = t;
            t = y;

            y = x - q * y;
            x = t;
        }

        if (x < 0) x += m0;

        return x;
    }
};

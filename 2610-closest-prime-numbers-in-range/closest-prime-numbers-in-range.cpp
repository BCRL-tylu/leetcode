#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        if (right < 2) return {-1, -1};

        // Step 1: Sieve of Eratosthenes to find primes up to 'right'
        vector<bool> isPrime(right + 1, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= right; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= right; j += i)
                    isPrime[j] = false;
            }
        }

        // Step 2: Collect primes in the range [left, right]
        vector<int> primes;
        for (int i = max(2, left); i <= right; i++) {
            if (isPrime[i]) primes.push_back(i);
        }

        // Step 3: Find the closest pair
        if (primes.size() < 2) return {-1, -1};

        vector<int> ans = {primes[0], primes[1]};
        int minDiff = ans[1] - ans[0];

        for (size_t i = 1; i < primes.size() - 1; i++) {
            int diff = primes[i + 1] - primes[i];
            if (diff < minDiff) {
                minDiff = diff;
                ans = {primes[i], primes[i + 1]};
            }
            if (minDiff == 2) break;  // Twin prime optimization
        }
        return ans;
    }
};

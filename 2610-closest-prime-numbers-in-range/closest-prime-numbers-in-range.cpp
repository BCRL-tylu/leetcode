#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        if (right < 2) return {-1, -1};
        if (left <= 2 && right >= 3)
            return { 2, 3 };

        // Step 1: Sieve of Eratosthenes to find primes up to 'right'
        vector<bool> isPrime(right + 1, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= right; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= right; j += i)
                    isPrime[j] = false;
            }
        }

        vector<int> ans = {-1,-1};
        int diff = 0, prev =0;
        for(int i =left; i<=right;i++){
            if(isPrime[i]){
                if(ans[0] == -1){
                    ans[0] = (int)i;
                    continue;
                }else if(ans[1] ==-1){
                    ans[1] = (int)i;
                    diff = ans[1]-ans[0];
                    prev = ans[1];
                    continue;
                }else{
                    if((int)i-prev<diff){
                        diff = (int)i-prev;
                        ans[0] = prev;
                        ans[1] = (int)i;
                    }
                    prev = (int)i;
                }
            }
        }
        if(ans[1] ==-1) return {-1,-1};
        return ans;
    }
};
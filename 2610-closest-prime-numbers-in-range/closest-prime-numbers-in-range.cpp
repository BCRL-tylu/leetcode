class Solution {
private:
    typedef unsigned long long ull;
    // Multiply a and b under modulo mod using 128-bit arithmetic to avoid
    // overflow.
    ull modmul(ull a, ull b, ull mod) {
        __int128 t = a;
        t *= b;
        t %= mod;
        return (ull)t;
    }

    // Fast modular exponentiation: computes (base^exp) % mod.
    ull modexp(ull base, ull exp, ull mod) {
        ull result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1)
                result = modmul(result, base, mod);
            base = modmul(base, base, mod);
            exp >>= 1;
        }
        return result;
    }

    // Miller-Rabin test to check if n is prime.
    // This deterministic version works for 64-bit integers.
    bool isPrime(ull n) {
        if (n < 2)
            return false;

        // Check small primes.
        int smallPrimes[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        for (int i = 0; i < 12; i++) {
            if (n == smallPrimes[i])
                return true;
            if (n % smallPrimes[i] == 0)
                return false;
        }

        // Write n-1 as d * 2^s.
        ull d = n - 1;
        int s = 0;
        while ((d & 1) == 0) {
            d >>= 1;
            s++;
        }

        // Set of bases to test (sufficient for 64-bit numbers).
        ull testPrimes[7] = {2ULL,      325ULL,     9375ULL,      28178ULL,
                             450775ULL, 9780504ULL, 1795265022ULL};
        for (ull a : testPrimes) {
            if (a % n == 0)
                continue; // a is not a valid witness if a is a multiple of n.
            ull x = modexp(a, d, n);
            if (x == 1 || x == n - 1)
                continue;
            bool composite = true;
            for (int r = 1; r < s; r++) {
                x = modmul(x, x, n);
                if (x == n - 1) {
                    composite = false;
                    break;
                }
            }
            if (composite)
                return false;
        }
        return true;
    }

public:
    vector<int> closestPrimes(int left, int right) {
        vector<int> ans = {-1,-1};
        int diff = 0, prev =0;
        for(ull i =left; i<=right;i++){
            if(isPrime(i)){
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
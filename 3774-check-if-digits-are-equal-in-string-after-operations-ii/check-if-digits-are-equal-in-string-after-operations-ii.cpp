class Solution {
public:
    // Compute binom(n, k) mod 2.
    // A well known fact is that binom(n, k) is odd (≡ 1 mod 2)
    // if and only if for every bit position, the binary digit of k
    // is ≤ that of n.
    int binom_mod_2(int n, int k) {
        while(n || k) {
            if ((k & 1) > (n & 1))
                return 0;
            n >>= 1;
            k >>= 1;
        }
        return 1;
    }
    
    // Precomputed small binomials mod 5 for n, k in {0,1,2,3,4}.
    // Note: 4 choose 2 = 6, and 6 mod 5 = 1.
    int smallBinom[5][5] = {
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 2, 1, 0, 0},
        {1, 3, 3, 1, 0},
        {1, 4, 1, 4, 1}
    };
    
    // Compute binom(n, k) mod 5 using Lucas’s theorem.
    int binom_mod_5(int n, int k) {
        int res = 1;
        while(n > 0 || k > 0) {
            int n_digit = n % 5;
            int k_digit = k % 5;
            if(k_digit > n_digit)
                return 0;
            res = (res * smallBinom[n_digit][k_digit]) % 5;
            n /= 5;
            k /= 5;
        }
        return res;
    }
    
    // Combine the mod 2 and mod 5 parts to get binom(n, k) mod 10.
    // If we have:
    //     x ≡ mod2 (mod 2)  and  x ≡ mod5 (mod 5),
    // then the two possibilities mod 10 are mod5 and mod5+5.
    int binom_mod_10(int n, int k) {
        int mod2 = binom_mod_2(n, k);  // Either 0 or 1.
        int mod5 = binom_mod_5(n, k);  // In the range 0..4.
        // Choose x from {mod5, mod5+5} so that x mod 2 equals mod2.
        if ((mod5 % 2) == mod2)
            return mod5;
        else
            return mod5 + 5;
    }
    
    bool hasSameDigits(string s) {
        int L = s.size();
        if (L < 2)
            return false;  // Edge case.
        int n = L - 2;  // The number of steps (the binomial row index).
        
        int left = 0, right = 0;
        // For 0 <= i <= n, compute the weighted sums.
        for (int i = 0; i <= n; i++) {
            int coef = binom_mod_10(n, i);
            left = (left + coef * (s[i] - '0')) % 10;
            right = (right + coef * (s[i + 1] - '0')) % 10;
        }
        return left == right;
    }
};

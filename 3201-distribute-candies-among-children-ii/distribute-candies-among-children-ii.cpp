class Solution {
public:
    long long distributeCandies(int n, int limit) {
        long long L = limit;
        // Case 1: 0 <= n <= L
        if (n <= L) {
            return (long long)(n + 1) * (n + 2) / 2;
        }
        // Case 2: L < n <= 2L
        if (n <= 2*L) {
            // First‐sum = Σ_{i=0..(n−L)} [2L - (n - i) + 1]
            long long u = n;  // since n <= 2L
            long long first =
                (3*L - u + 2) * (u - L + 1) / 2;

            // Second‐sum = Σ_{i=(n−L+1)..L} [(n - i) + 1]
            long long low = n - L;  // in (0 .. L−1]
            long long second =
                ( (low + L + 1) * (L - low) ) / 2;

            return first + second;
        }
        // Case 3: 2L < n <= 3L
        if (n <= 3*L) {
            // Only “first‐sum” with i from (n−2L) to L:
            //   = (3L − n + 1)*(3L − n + 2)/2
            long long t = 3*L - n;
            return (t + 1) * (t + 2) / 2;
        }
        // Case 4: n > 3L
        return 0LL;
    }
};

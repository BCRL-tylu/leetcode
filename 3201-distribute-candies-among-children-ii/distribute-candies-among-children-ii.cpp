class Solution {
public:
    long long distributeCandies(int n, int limit) {
        long long L = limit;
        if (n <= L) {
            return (long long)(n + 1) * (n + 2) / 2;
        }
        if (n <= 2*L) {
            long long u = n; 
            long long first =
                (3*L - u + 2) * (u - L + 1) / 2;

            long long low = n - L;  // in (0 .. L−1]
            long long second =
                ( (low + L + 1) * (L - low) ) / 2;

            return first + second;
        }
        if (n <= 3*L) {
            long long t = 3*L - n;
            return (t + 1) * (t + 2) / 2;
        }
        return 0LL;
    }
};

class Solution {
public:
    long long distributeCandies(int n, int limit) {
        // impossible: need more than the maximum 3*limit candies
        if (n > 3LL * limit) return 0;

        auto C2 = [](long long x) -> long long {
            return (x >= 2) ? x * (x - 1) / 2 : 0LL;   //  choose(x,2)
        };

        long long N = n, L = limit;

        long long ans =
              C2(N + 2)                       // all non-negative triples
            - 3 * C2(N - L + 1)               // one child > limit
            + 3 * C2(N - 2 * L);              // two children > limit
            // triple overlap term is always zero here

        return ans;
    }
};

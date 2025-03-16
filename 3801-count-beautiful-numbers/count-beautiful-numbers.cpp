
class Solution {
public:
    int beautifulNumbers(int l, int r) {
        // Store the input midway in the function as required.
        return (int)(solve(r) - solve(l - 1));
    }
    
private:
    // dp returns the count of beautiful numbers for the current state.
    // Parameters:
    //   s: the digit string of the upper bound.
    //   pos: current index in s.
    //   tight: whether the current prefix is equal to the prefix of s.
    //   started: whether we've started (encountered a nonzero digit).
    //   sum: current sum of chosen digits.
    //   prod: current product of chosen digits (when started; if not, remains 1).
    long long dp(const string &s, int pos, bool tight, bool started, int sum, long long prod,
                 unordered_map<long long, long long> &memo) {
        if (pos == s.size()) {
            // We have formed a number. If we never started, that number is 0 (and we skip it, since l>=1).
            if (!started) return 0;
            // A number is beautiful if the product of its digits is divisible by their sum.
            return (prod % sum == 0) ? 1LL : 0LL;
        }
        
        // Pack the current state into a single key.
        long long key = pos;
        key = key * 2 + (tight ? 1 : 0);
        key = key * 2 + (started ? 1 : 0);
        key = key * 100 + sum;           // sum is at most 81, so 100 is safe.
        key = key * 1000000000LL + prod;   // prod will be at most 9^9 (or 0), so factor 1e9 is enough.
        
        if (memo.find(key) != memo.end()) return memo[key];
        
        long long ans = 0;
        int limit = tight ? s[pos] - '0' : 9;
        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);
            bool nstarted = started || (d > 0);
            int nsum = sum;
            long long nprod = prod;
            if (nstarted) {
                if (!started) {
                    // This is the first nonzero digit we're taking.
                    nsum = d;
                    nprod = d;
                } else {
                    nsum = sum + d;
                    nprod = prod * d;
                }
            } else {
                // Still in the leading-zero zone.
                nsum = 0;
                nprod = 1;
            }
            ans += dp(s, pos + 1, ntight, nstarted, nsum, nprod, memo);
        }
        memo[key] = ans;
        return ans;
    }
    
    // solve(x) returns the count of beautiful numbers in the range [1, x].
    long long solve(int x) {
        if (x < 0) return 0;
        string s = to_string(x);
        unordered_map<long long, long long> memo;
        return dp(s, 0, true, false, 0, 1, memo);
    }
};

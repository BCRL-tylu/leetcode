class Solution {
private:
    vector<int> find_valid_b(int a, int size) {
        int target = (1 << size) - 1; // All bits set to 1 for given size
        int mask = target ^ a;        // Positions where `a` has 0s

        std::vector<int> results;
        for (int b = 0; b <= target; b++) {
            if ((b & mask) == mask) { // Ensure b fills all 0s in a
                results.push_back(b);
            }
        }
        return results;
    }

    long long lcm(long long a, long long b) { return (a * b) / std::__gcd(a, b); }

    // Function to calculate the LCM of multiple numbers
    long long lcmMultiple(const std::vector<long long>& numbers) {
        long long result = 1;
        for (long long num : numbers) {
            result = lcm(result, num);
        }
        return result;
    }

public:
    long long minimumIncrements(vector<int>& nums, vector<int>& target) {
        int n = target.size();
        vector<long long> hm(1 << n); // Initialize hm with size 2^n
        vector<long long> dp(1 << n, LLONG_MAX); // Initialize dp with size 2^n

        for (int i = 1; i < (1 << n); ++i) {
            std::vector<long long> selected;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    selected.push_back(target[j]);
                }
            }
            long long lcmValue = lcmMultiple(selected);
            hm[i] = lcmValue;
        }
        dp[0] = 0;
        for (int num : nums) {
            long long min_diff = LLONG_MAX; // Initialize to a large value
            vector<long long> comb_cost(1 << n, 0);
            for (int i = 1; i < (1 << n); ++i) {
                long long cost;
                // Compute cost for each combination
                if (num % hm[i] == 0) {
                    cost = 0;
                } else {
                    cost = ((num / hm[i] + 1) * hm[i] - num) % hm[i]; // Compute the smallest difference
                }
                comb_cost[i] = cost;
            }
            vector<long long> newdp = dp;

            for (int i = 0; i < (1 << n); ++i) {
                if (dp[i] == LLONG_MAX) continue;
                for (int j = 1; j < (1 << n); ++j) {
                    long long nmask = i | j;
                    long long ncost = dp[i] + comb_cost[j];
                    if (ncost < newdp[nmask]) {
                        newdp[nmask] = ncost;
                    }
                }
            }
            dp = newdp;
        }
        if (dp.back() == LLONG_MAX) return -1;
        return dp.back();
    }
};

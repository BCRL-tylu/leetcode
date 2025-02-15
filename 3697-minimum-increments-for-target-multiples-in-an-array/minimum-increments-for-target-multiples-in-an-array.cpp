class Solution {
private:
    using ll = long long; // Define ll as a shorthand for long long

    // Generate valid values of b that fill all 0s in a
    vector<int> findValidB(int a, int size) {
        int target = (1 << size) - 1; // All bits set to 1 for given size
        int mask = target ^ a; // Positions where `a` has 0s
        vector<int> results;

        for (int b = 0; b <= target; b++) {
            if ((b & mask) == mask) { // Ensure b fills all 0s in a
                results.push_back(b);
            }
        }
        return results;
    }

    // Calculate the LCM of two numbers
    ll lcm(ll a, ll b) {
        return (a * b) / std::__gcd(a, b);
    }

    // Calculate the LCM of multiple numbers
    ll lcmMultiple(const vector<ll>& numbers) {
        ll result = 1;
        for (ll num : numbers) {
            result = lcm(result, num);
        }
        return result;
    }

public:
    ll minimumIncrements(vector<int>& nums, vector<int>& target) {
        int n = target.size();
        vector<ll> hm(1 << n); // Initialize hm with size 2^n
        vector<ll> dp(1 << n, LLONG_MAX); // Initialize dp with size 2^n

        // Precompute LCM values for all combinations of target
        for (int i = 1; i < (1 << n); ++i) {
            vector<ll> selected;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    selected.push_back(target[j]);
                }
            }
            hm[i] = lcmMultiple(selected);
        }

        dp[0] = 0; // Base case
        // for each number we need to calculate the optimal cost
        for (int num : nums) {
            vector<ll> combCost(1 << n, 0);

            // Compute cost for each combination based on current num
            for (int i = 1; i < (1 << n); ++i) {
                combCost[i]  = (num % hm[i] == 0) ? 0 : ((num / hm[i] + 1) * hm[i] - num) % hm[i];
            }
            vector<ll> newDp = dp; // Temporary copy of dp
            // Update dp based on the computed costs
            for (int i = 0; i < (1 << n); ++i) {
                // retain a copy of origianl dp
                if (dp[i] == LLONG_MAX) continue; // Skip unreachable states
                for (int j = 1; j < (1 << n); ++j) { // update the original dp by 
                    int nmask = i | j; // initially j since i = 0 
                    newDp[nmask] = min(newDp[nmask],dp[i] + combCost[j]); // calcualte the cost based on current cost on the bitcombination
                }
            }
            dp = newDp; // Update dp for the next number
        }
        return dp.back() == LLONG_MAX ? -1 : dp.back(); // Return the result
    }
};

class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int m = queries.size(), n = nums.size();
        int L = 0, R = m, ans = -1;
        
        while (L <= R) {
            int mid = L + (R - L) / 2;
            if (check(mid, nums, queries)) {
                ans = mid;
                R = mid - 1;  // Try to find a smaller k
            } else {
                L = mid + 1;  // We need more queries
            }
        }
        return ans;
    }

private:
    bool check(int k, vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        // For each index, we try to see if we can select a subset of queries (among the first k)
        // covering that index to exactly sum up to nums[i].
        for (int i = 0; i < n; i++) {
            int target = nums[i];
            vector<bool> dp(target + 1, false);
            dp[0] = true;
            // Process the first k queries
            for (int j = 0; j < k; j++) {
                // Only consider query j if it affects index i
                if (queries[j][0] <= i && i <= queries[j][1]) {
                    int val = queries[j][2];
                    // Standard subset-sum update (0/1 knapsack) updating backwards
                    for (int t = target; t >= val; t--) {
                        if (dp[t - val]) {
                            dp[t] = true;
                        }
                    }
                }
            }
            // If we cannot form the sum equal to nums[i], then index i cannot be zeroed.
            if (!dp[target]) return false;
        }
        return true;
    }
};

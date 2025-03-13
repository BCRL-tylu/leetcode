class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), k = queries.size();
        // We'll cache computed cumulative arrays:
        // cache[x] stores the cumulative array after applying the first x queries.
        unordered_map<int, vector<int>> cache;
        
        // Helper: compute cumulative array for candidate 'mid'
        auto computeCum = [&](int mid) -> vector<int> {
            // If already computed, return it.
            if (cache.count(mid))
                return cache[mid];
            
            // Try to find a cached candidate that is the largest candidate <= mid.
            int baseIdx = 0;
            for (auto &entry : cache) {
                if (entry.first <= mid && entry.first > baseIdx)
                    baseIdx = entry.first;
            }
            
            // Start with the previously computed cumulative array if available,
            // otherwise start with all zeros.
            vector<int> cum = (baseIdx > 0 ? cache[baseIdx] : vector<int>(n, 0));
            
            // Use a diff array to apply queries from baseIdx to mid - 1.
            vector<int> diff(n + 1, 0);
            for (int i = baseIdx; i < mid; i++) {
                int l = queries[i][0], r = queries[i][1], val = queries[i][2];
                diff[l] += val;
                if (r + 1 < n)
                    diff[r + 1] -= val;
            }
            // Now update cum by adding the effect of diff.
            int add = 0;
            for (int j = 0; j < n; j++) {
                add += diff[j];
                cum[j] += add;
            }
            // Cache this result.
            cache[mid] = cum;
            return cum;
        };
        
        // Binary search for the minimum number of queries required.
        int low = 0, high = k + 1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            vector<int> cum = computeCum(mid);
            bool valid = true;
            for (int j = 0; j < n; j++) {
                if (cum[j] < nums[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                high = mid;
            } else {
                low = mid + 1;
                vector<int> keysToRemove;
                for (auto &entry : cache) {
                    if (entry.first < low)
                        keysToRemove.push_back(entry.first);
                }
                for (int key : keysToRemove)
                    cache.erase(key);
            }
        }
        return (low <= k ? low : -1);
    }
};

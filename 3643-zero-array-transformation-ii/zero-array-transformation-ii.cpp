class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), k = queries.size();
        unordered_map<int, vector<int>> cache;
        set<int> cachedIds;
        cache[0] = vector<int>(n, 0);
        cachedIds.insert(0);
        
        auto computeCum = [&](int mid) -> vector<int> {
            // If we already computed the cumulative array for 'mid' queries, return it.
            if (cache.count(mid))
                return cache[mid];
            
            int baseIdx = 0;
            auto it = cachedIds.upper_bound(mid);
            if (it != cachedIds.begin()){
                it--;
                baseIdx = *it;
            }
            
            vector<int> cum = cache[baseIdx];
            
            vector<int> diff(n + 1, 0);
            for (int i = baseIdx; i < mid; i++) {
                int l = queries[i][0], r = queries[i][1], val = queries[i][2];
                diff[l] += val;
                // Since our diff array is of size n+1, we can update index r+1 directly.
                if (r + 1 < (int)diff.size())
                    diff[r + 1] -= val;
            }
            int add = 0;
            for (int j = 0; j < n; j++){
                add += diff[j];
                cum[j] += add;
            }
            cache[mid] = cum;
            cachedIds.insert(mid);
            return cum;
        };
        
        int low = 0, high = k + 1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            vector<int> cum = computeCum(mid);
            bool valid = true;
            for (int j = 0; j < n; j++){
                if (cum[j] < nums[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                high = mid;
            } else {
                low = mid + 1;
                auto it = cachedIds.lower_bound(low);
                for (auto iter = cachedIds.begin(); iter != it; ) {
                    if (*iter != 0) {  // Never remove candidate 0.
                        cache.erase(*iter);
                        iter = cachedIds.erase(iter);
                    } else {
                        ++iter;
                    }
                }
            }
        }
        return (low <= k ? low : -1);
    }
};

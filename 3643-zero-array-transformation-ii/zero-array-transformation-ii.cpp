class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), k = queries.size();
        auto canZero = [&](int mid) -> bool {
            vector<int> diff(n + 1, 0); 
            for (int i = 0; i < mid; i++){
                int l = queries[i][0], r = queries[i][1], val = queries[i][2];
                diff[l] += val;
                if (r + 1 < n) diff[r + 1] -= val;
            }
            int current = 0;
            for (int j = 0; j < n; j++){
                current += diff[j];
                if (current < nums[j])
                    return false;
            }
            return true;
        };
        
        int l = 0, r = k + 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (canZero(mid))
                r = mid;
            else
                l = mid + 1;
        }
        return (l <= k ? l : -1);
    }
};

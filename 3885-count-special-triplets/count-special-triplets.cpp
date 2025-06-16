class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        unordered_map<int, int> lmp, rmp;
        int n = nums.size();
        for (auto k : nums) {
            rmp[k]++;
        }
        lmp[nums[0]]++;
        rmp[nums[0]]--;
        long long ans = 0, mod = 1e9 + 7;
        for (int i = 1; i < n - 1; i++) {
            rmp[nums[i]]--;
            int u = nums[i] << 1;
            ans += ((lmp[u] % mod) * (rmp[u] % mod)) % mod;
            ans%=mod;
            lmp[nums[i]]++;
        }
        return (int)ans;
    }
};
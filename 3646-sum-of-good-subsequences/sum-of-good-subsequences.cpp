class Solution {
public:
    typedef long long ll;
    const int mod = 1000000007;

    int sumOfGoodSubsequences(vector<int>& nums) {
         int n = nums.size();
         unordered_map<ll, ll> mp;
         unordered_map<ll, ll> index1;
         mp[nums[0]] = 1;
         ll ans = 0;

         for (int i = 1; i < n; i++) {
              if (mp.find(nums[i] - 1) != mp.end()) {
                 index1[i] = (index1[i] + mp[nums[i] - 1]) % mod;
              }
              if (mp.find(nums[i] + 1) != mp.end()) {
                 index1[i] = (index1[i] + mp[nums[i] + 1]) % mod;
              }
              mp[nums[i]] = (mp[nums[i]] + 1 + index1[i]) % mod;
         }

         unordered_map<int, int> mp1;
         unordered_map<int, ll> index2;
         mp1[nums[n - 1]] = 1;

         for (int i = n - 2; i >= 0; i--) {
            if (mp1.find(nums[i] - 1) != mp1.end()) {
                 index2[i] = (index2[i] + mp1[nums[i] - 1]) % mod;
              }
              if (mp1.find(nums[i] + 1) != mp1.end()) {
                index2[i] = (index2[i] + mp1[nums[i] + 1]) % mod;
              }
              mp1[nums[i]] = (mp1[nums[i]] + 1 + index2[i]) % mod;
         }

         for (int i = 0; i < n; i++) {
            ll xx = 0;

            if (index1.find(i) != index1.end() && index2.find(i) != index2.end()) {
                xx = (xx + nums[i] * index1[i] % mod * index2[i] % mod) % mod;
            }
            if (index1.find(i) != index1.end()) {
                xx = (xx + nums[i] * index1[i] % mod) % mod;
            }
            if (index2.find(i) != index2.end()) {
                xx = (xx + nums[i] * index2[i] % mod) % mod;
            }
            xx = (xx + nums[i]) % mod;
            ans = (ans + xx) % mod;
         }

         return ans;
    }
};
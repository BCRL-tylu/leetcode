class Solution {
    using ll = long long int;
    constexpr static int mod = 1e9 + 7; 
public:
    int sumOfGoodSubsequences(vector<int>& nums) {
        int mx  = *max_element(nums.begin(), nums.end());
        vector<ll> count(mx + 2), sum(mx + 2);
        ll ans = 0;
        for(auto num : nums){
            ll ttCount = (num - 1 >= 0 ? count[num - 1] : 0) + count[num + 1];
            ttCount++;
            ttCount %= mod;

            ll ttSum  = (num - 1 >= 0 ? sum[num - 1] : 0 ) + sum[num + 1];
            ttSum %= mod;

            (count[num] += ttCount) %= mod;
            (sum[num] += ttSum + ttCount * num) %= mod;
        }

        for(auto u: sum) (ans += u ) %= mod;
        return ans;
    }
};
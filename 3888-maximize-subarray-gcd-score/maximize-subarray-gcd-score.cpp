#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxGCDScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> e2(n), odd(n);
        for (int i = 0; i < n; ++i) {
            e2[i]  = __builtin_ctz(nums[i]);
            odd[i] = nums[i] >> e2[i];
        }
        
        long long ans = 0;
        for (int l = 0; l < n; ++l) {
            array<int,31> freq = {};
            int cur_gcd = 0;
            
            for (int r = l; r < n; ++r) {
                if (r == l) 
                    cur_gcd = odd[r];
                else 
                    cur_gcd = gcd(cur_gcd, odd[r]);
                
                freq[e2[r]]++;

                int min_e2 = 0;
                while (min_e2 < 31 && freq[min_e2] == 0)
                    ++min_e2;

                int cnt = freq[min_e2];
                int E = min_e2 + (cnt <= k ? 1 : 0);
                long long gcd_tot = (long long)cur_gcd << E;
                long long score   = gcd_tot * (r - l + 1LL);
                
                ans = max(ans, score);
            }
        }
        
        return ans;
    }
};

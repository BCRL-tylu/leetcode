class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int M = *max_element(nums.begin(), nums.end());
        
        long long ans = 0;
        int cnt = 0; 
        int l = 0;     
        for (int r = 0; r < n; ++r) {
            if (nums[r] == M)
                ++cnt;
    
            while (cnt >= k) {
                ans += (n - r);
                if (nums[l] == M)
                    --cnt;
                ++l;
            }
        }
        
        return ans;
    }
};

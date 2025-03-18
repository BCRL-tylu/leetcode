class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int l = 0, r = 0, n = nums.size(), ans = 0, c = 0;
        
        while (r < n) {
            while ((c & nums[r]) != 0) {  // Ensure AND condition holds
                c ^= nums[l];  // Remove nums[l] bits
                l++;  // Move left pointer
            }
            c |= nums[r];  // Add nums[r] bits
            ans = max(ans, r - l + 1);  // Update max length
            r++;  // Move right pointer
        }
        
        return ans;
    }
};

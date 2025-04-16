class Solution {
public:
    long long countGood(vector<int>& nums, int k) {

        reverse(nums.begin(), nums.end());
        
        int n = nums.size();
        long long ans = 0;
        long long pairs = 0;  // current number of pairs in window
        unordered_map<int, int> freq;
        int left = 0, right = 0;
        
        while(left < n) {
            while(right < n && pairs < k) {

                pairs += freq[nums[right]];
                freq[nums[right]]++;
                right++;
            }
            if(pairs >= k)
                ans += (n - right + 1);
            
            freq[nums[left]]--;
            pairs -= freq[nums[left]];
            left++;
        }
        return ans;
    }
};

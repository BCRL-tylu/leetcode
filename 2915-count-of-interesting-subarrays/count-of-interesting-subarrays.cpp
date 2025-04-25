class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        unordered_map<int, long long> freq;
        freq[0] = 1; 
        long long ans = 0;
        int count = 0;

        for (int num : nums) {
            if (num % modulo == k) count++;
            int mod = count % modulo;
            int target = (mod - k + modulo) % modulo;
            ans += freq[target];
            freq[mod]++;
        }
        return ans;
    }
};

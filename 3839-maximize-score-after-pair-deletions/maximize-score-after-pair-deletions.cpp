class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        if (n % 2 == 0) {
            int minPair = INT_MAX;
            for (int i = 0; i < n - 1; i++) {
                minPair = min(minPair, nums[i] + nums[i + 1]);
            }
            return totalSum - minPair;
        } else {
            int minElement = *min_element(nums.begin(), nums.end());
            return totalSum - minElement;
        }
    }
};

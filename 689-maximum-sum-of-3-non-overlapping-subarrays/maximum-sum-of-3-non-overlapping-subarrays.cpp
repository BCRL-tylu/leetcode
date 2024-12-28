class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> windowSum(n - k + 1, 0);
        
        // Step 1: Compute window sums
        int current_sum = accumulate(nums.begin(), nums.begin() + k, 0);
        windowSum[0] = current_sum;
        
        for (int i = 1; i <= n - k; ++i) {
            current_sum += nums[i + k - 1] - nums[i - 1];
            windowSum[i] = current_sum;
        }
        
        // Step 2: Generate arrays A and B
        vector<pair<int, int>> A(n - k + 1), B(n - k + 1); // {max sum, index}
        
        // Populate B (maximum value before index i)
        int max_value = windowSum[0], max_index = 0;
        for (int i = 0; i <= n - k; ++i) {
            if (windowSum[i] > max_value) {
                max_value = windowSum[i];
                max_index = i;
            }
            B[i] = {max_value, max_index};
        }
        // Populate A (maximum value after index i)
        max_value = windowSum[n - k];
        max_index = n - k;
        for (int i = n - k; i >= 0; --i) {
            if (windowSum[i] >= max_value) { // Use >= to ensure lexicographical order
                max_value = windowSum[i];
                max_index = i;
            }
            A[i] = {max_value, max_index};
        }
        // Step 3: Find the maximum combined sum
        int max_sum = 0;
        vector<int> result(3, 0);
        
        for (int i = k; i <= n - 2 * k; ++i) {
            int left_sum = B[i - k].first;
            int left_index = B[i - k].second;
            int middle_sum = windowSum[i];
            int right_sum = A[i + k].first;
            int right_index = A[i + k].second;
            int total_sum = left_sum + middle_sum + right_sum;
            if (total_sum > max_sum) {
                max_sum = total_sum;
                result = {left_index, i, right_index};
            }
        }
        
        return result;
    }
};

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;
        for (auto& row : grid) {
            for (int val : row) {
                nums.push_back(val);
            }
        }

        // Check if all elements are congruent modulo x
        int remainder = nums[0] % x;
        for (int num : nums) {
            if (num % x != remainder) return -1;
        }

        // Sort the array and find the median
        sort(nums.begin(), nums.end());
        int median = nums[nums.size() / 2];

        // Compute the total number of operations
        int operations = 0;
        for (int num : nums) {
            operations += abs(num - median) / x;
        }

        return operations;
    }
};

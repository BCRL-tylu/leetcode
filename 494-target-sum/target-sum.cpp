class Solution {
    private:
    int dfs(const vector<int>& nums, int target, int index, int currentSum) {
        if (index == nums.size()) {
            // Base case: check if the current sum equals the target
            return currentSum == target ? 1 : 0;
        }
        
        // Recursive case: explore '+' and '-' branches
        int add = dfs(nums, target, index + 1, currentSum + nums[index]);
        int subtract = dfs(nums, target, index + 1, currentSum - nums[index]);
        return add + subtract;
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        return dfs(nums, abs(target), 0, 0);
    }
};
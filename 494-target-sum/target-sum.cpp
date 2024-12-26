class Solution {
    private:
    int dfs(const vector<int>& nums,const vector<int>& cumsum, int target, int index, int currentSum) {
        if (index == nums.size()) {
            // Base case: check if the current sum equals the target
            return currentSum == target ? 1 : 0;
        }else{
            if(currentSum+cumsum[index]<target){
                return 0;
            }
        }
        
        // Recursive case: explore '+' and '-' branches
        int add = dfs(nums, cumsum,target, index + 1, currentSum + nums[index]);
        int subtract = dfs(nums, cumsum, target, index + 1, currentSum - nums[index]);
        return add + subtract;
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> cumSum(n);
        cumSum[n-1] = nums[n-1];
for (int i = n - 2; i >= 0; --i) {
    cumSum[i] = cumSum[i + 1] + nums[i];
}
        return dfs(nums,cumSum, abs(target), 0, 0);
    }
};
class Solution {
private:
void generate(int index, std::vector<int>& nums, std::vector<std::vector<int>>& results) {
    if (index == nums.size()) {
        results.push_back(nums);  // Store the current permutation
        return;
    }
    for (int i = index; i < nums.size(); i+=2) {
        std::swap(nums[index], nums[i]);  // Swap current element with index
        generate(index+1, nums,results); // Recur for next index
        std::swap(nums[index], nums[i]);  // Undo swap (backtrack)
    }
}
public:
    vector<vector<int>> permute(int n) {
        vector<int> nums,enums;
    for(int i =1; i<=n;i+=2){
        nums.push_back(i);
        if(i+1<=n){
        nums.push_back(i+1);
        enums.push_back(i+1);
        }
        enums.push_back(i);
    }


    std::vector<std::vector<int>> results;
    generate(0, nums, results);
    if(n%2==0){
        generate(0, enums, results);
    }
    sort(results.begin(),results.end());
    return results;
    }
};
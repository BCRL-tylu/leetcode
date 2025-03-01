class Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        vector<int> ans;
        int zc =0, n = nums.size();
        for(int i = 0; i<n-1;i++){
            if(nums[i] == nums[i+1]){
                if(nums[i]==0){
                    zc+=1;
                }else{
                    ans.push_back(nums[i]<<1);
                    nums[i+1] = 0;
                }
            }else{
                if(nums[i]!=0){
                    ans.push_back(nums[i]);
                }else{
                    zc++;
                }
            }
        }

        if(nums[n-1] != nums[n-2]){
            ans.push_back(nums[n-1]);
        }else{
            ans.push_back(0);
        }
        for(int i =0; i<zc;i++){
            ans.push_back(0);
        }
        return ans;
    }
};
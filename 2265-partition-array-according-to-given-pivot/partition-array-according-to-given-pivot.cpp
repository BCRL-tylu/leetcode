class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> be,af;
        int n = nums.size(), k = 0;
        for(int i = 0; i<n;i++){
            if(nums[i]<pivot){
                be.push_back(nums[i]);
            }else if(nums[i]>pivot){
                af.push_back(nums[i]);
            }else{
                k++;
            }
        }

        for(int i = 0; i<k;i++){
            be.push_back(pivot);
        }
        for(int i = 0; i<(int)af.size();i++){
            be.push_back(af[i]);
        }
        return be;
    }
};
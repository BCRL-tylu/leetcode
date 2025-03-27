class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        unordered_map<int,int>right,left;
        int n=nums.size(),l=0,r=n;
        for(auto k:nums)right[k]++;

        for(int i=0;i<n;i++){
            left[nums[i]]++;
            right[nums[i]]--;
            if(left[nums[i]]>=((i+1)>>1)+1 && right[nums[i]]>=((n-i-1)>>1)+1){
                return i;
            }
        }
        return -1;
    }
};
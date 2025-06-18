#include<bits/stdc++.h>
class Solution {
public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        for(int i=0;i<n-2;i+=3){
            if(abs(nums[i]-nums[i+2])>k) return {};
            res.push_back({nums[i],nums[i+1],nums[i+2]});
        }
        return res;
    }
};
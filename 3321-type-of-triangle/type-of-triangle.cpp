class Solution {
public:
    string triangleType(vector<int>& nums) {
        for(int i =0;i<3;i++){
            if(nums[i%3]+nums[(i+1)%3]<=nums[(i+2)%3]){
                return "none";
            }
        }
        if(nums[0]==nums[1]&&nums[1]==nums[2]){
            return "equilateral";
        }
        for(int i =0;i<3;i++){
            if(nums[i%3]==nums[(i+1)%3]){
                return "isosceles";
            }
        }
        return "scalene";
    }
};
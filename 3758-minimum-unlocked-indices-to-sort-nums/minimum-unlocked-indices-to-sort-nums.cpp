class Solution {
public:
    int minUnlockedIndices(vector<int>& nums, vector<int>& locked) {
        int ones = 0; 
        int twos = 0; 
        int threes = 0; 
        int pos = 0;
        int ret = 0;
        vector<int> sums(nums.size());
        sums[0] = locked[0]; 
        for(int i = 1;i<locked.size();i++) {
            sums[i] = sums[i-1] + locked[i];
        }
        for(int i = 0;i<nums.size();i++) {
            if(nums[i] == 1) {
                if(threes > 0) {
                    return -1;
                }
                if(twos > 0) {
                    int l = max(pos, ones);
                    ret += sums[i-1] - sums[l] + locked[l];
                    pos = i;
                }
                ones++;
            } else if(nums[i] == 2) {
                if(threes > 0) {
                    int l = max(ones + twos, pos); 
                    ret += sums[i-1] - sums[l] + locked[l];
                    pos = i;
                }
                twos++; 
            } else {
                threes++; 
            }
        }
        return ret; 
    }
};
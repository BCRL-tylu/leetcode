class Solution {
public:
    int minUnlockedIndices(vector<int>& nums, vector<int>& locked) {
        int minUnlocked = 0;
        for (int i = 0, numLocksFromMax = 0, maxNum = INT_MIN; i < nums.size(); ++i) {
            if (maxNum < nums[i]) {
                maxNum          = nums[i];
                numLocksFromMax = 0;
            }
            else if (maxNum > nums[i]) {
                if (maxNum > (nums[i]+1))
                    return -1;

                minUnlocked += exchange(numLocksFromMax, 0);
            }
            numLocksFromMax += locked[i];
        }
        return minUnlocked;
    }
};
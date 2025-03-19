class Solution {
public:
    int minUnlockedIndices(vector<int>& nums, vector<int>& locked) {
        int minUnlocked = 0; // This will hold the total unlock operations needed.
        // We initialize three variables in the for loop:
        // i: current index.
        // numLocksFromMax: number of locked indices since the last (current) maximum was seen.
        // maxNum: the current maximum value seen so far.
        for (int i = 0, numLocksFromMax = 0, maxNum = -1; i < nums.size(); ++i) {
            // If we find a new maximum value in nums, update maxNum.
            // When this happens, reset the count of locked indices since now the "new maximum" starts here.
            if (maxNum < nums[i]) {
                maxNum = nums[i]; // update the current maximum number
                numLocksFromMax = 0; // reset the lock count since new max resets the region.
            }
            // If the current number is less than the maximum seen so far, then an inversion is present.
            // According to the rules, the only allowed difference is exactly 1.
            else if (maxNum > nums[i]) {
                // If the difference is more than 1 (i.e. maxNum > nums[i] + 1),
                // then a disallowed swap (like a 3 and a 1) is encountered.
                if (maxNum > (nums[i] + 1))
                    return -1; // unsortable situation (e.g., 3 cannot be swapped with 1)

                // Otherwise, the difference is exactly 1.
                // We need to unlock all the locked indices that we encountered since the last max.
                // The exchange(numLocksFromMax, 0) does two things:
                // 1. It returns the current value of numLocksFromMax.
                // 2. It resets numLocksFromMax to 0.
                // We add that number to minUnlocked because those locks must be removed to allow a swap.
                minUnlocked += numLocksFromMax;
                numLocksFromMax =0;
            }
            // At each index, add the lock status (0 or 1) to numLocksFromMax.
            // This accumulates how many locked indices we have seen since the last max.
            numLocksFromMax += locked[i];
        }
        return minUnlocked;
    }
};

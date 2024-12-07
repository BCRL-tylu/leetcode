#include <vector>
#include <algorithm>

class Solution {
public:
    bool canAchieveMaxSize(std::vector<int>& nums, int maxOperations, int target) {
        int operationsNeeded = 0;
        
        for (int num : nums) {
            if (num > target) {
                // Calculate how many operations are needed to reduce num to target
                operationsNeeded += (num - 1) / target; // This gives the number of splits needed
            }
        }
        
        return operationsNeeded <= maxOperations;
    }
    
    int minimumSize(std::vector<int>& nums, int maxOperations) {
        int left = 1; // The smallest possible value
        int right = *std::max_element(nums.begin(), nums.end()); // The largest value in nums
        int result = right; // Start with the maximum value
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canAchieveMaxSize(nums, maxOperations, mid)) {
                result = mid; // If we can achieve this mid, it's a candidate
                right = mid - 1; // Try for a smaller maximum size
            } else {
                left = mid + 1; // Increase the guess
            }
        }
        
        return result; // Return the minimum possible maximum size
    }
};

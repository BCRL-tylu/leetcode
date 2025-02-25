class Solution {
public:
    long long largestEvenSum(vector<int>& nums, int k) {
    int n = nums.size();
    
    // Sort nums in descending order.
    nth_element(begin(nums), begin(nums) + k, end(nums), greater<int>());
    
    // Select the first k numbers as the candidate subsequence.
    long long sumCandidate = 0;
    // For candidate, track the smallest odd and smallest even.
    int candidateOddMin = -1, candidateEvenMin = -1;
    
    for (int i = 0; i < k; i++) {
        sumCandidate += nums[i];
        if (nums[i] % 2 == 0) { // even
            if (candidateEvenMin == -1 || nums[i] < candidateEvenMin)
                candidateEvenMin = nums[i];
        } else { // odd
            if (candidateOddMin == -1 || nums[i] < candidateOddMin)
                candidateOddMin = nums[i];
        }
    }
    
    // If the candidate sum is even, that's the answer.
    if (sumCandidate % 2 == 0)
        return sumCandidate;
    
    // From the remainder (indices k to n-1), get:
    //   - The largest even number (if any).
    //   - The largest odd number (if any).
    int remainderEvenMax = -1, remainderOddMax = -1;
    for (int i = k; i < n; i++) {
        if (nums[i] % 2 == 0) {
            remainderEvenMax = max(remainderEvenMax, nums[i]);
        } else {
            remainderOddMax = max(remainderOddMax, nums[i]);
        }
    }
    
    // Option 1: Remove the smallest odd in the candidate and add the largest even from remainder.
    long long option1 = -1;
    if (candidateOddMin != -1 && remainderEvenMax != -1) {
        option1 = sumCandidate - candidateOddMin + remainderEvenMax;
    }
    
    // Option 2: Remove the smallest even in the candidate and add the largest odd from remainder.
    long long option2 = -1;
    if (candidateEvenMin != -1 && remainderOddMax != -1) {
        option2 = sumCandidate - candidateEvenMin + remainderOddMax;
    }
    
    long long best = max(option1, option2);
    return best == -1 ? -1 : best;
    }
};
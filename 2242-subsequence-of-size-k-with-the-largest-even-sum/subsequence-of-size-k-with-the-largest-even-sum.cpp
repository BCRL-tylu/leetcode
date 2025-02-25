class Solution {
public:
    long long largestEvenSum(vector<int>& nums, int k) {
    int n = nums.size();

    
    // Sort nums in descending order.
    nth_element(begin(nums), begin(nums) + k, end(nums), greater<int>());
    //sort(nums.begin(), nums.end(), greater<int>());
    
    // Select the first k numbers as the candidate subsequence.
    long long sumCandidate = 0;
    // For candidate, track the smallest odd and smallest even.
    int com = INT_MAX, cem = INT_MAX;
    
    for (int i = 0; i < k; i++) {
        sumCandidate += nums[i];
        if (nums[i] % 2 == 0) { // even
                cem = min(nums[i],cem);
        } else { // odd
                com = min(nums[i],com);
        }
    }
    
    // If the candidate sum is even, that's the answer.
    if (sumCandidate % 2 == 0)
        return sumCandidate;
    
    // From the remainder (indices k to n-1), get:
    //   - The largest even number (if any).
    //   - The largest odd number (if any).
    int rem = -1, rom = -1;
    for (int i = k; i < n; i++) {
        if (nums[i] % 2 == 0) {
            rem = max(rem, nums[i]);
        } else {
            rom = max(rom, nums[i]);
        }
    }
    
    // Option 1: Remove the smallest odd in the candidate and add the largest even from remainder.
    long long option1 = -1;
    if (com != -1 && rem != -1) {
        option1 = sumCandidate - com + rem;
    }
    
    // Option 2: Remove the smallest even in the candidate and add the largest odd from remainder.
    long long option2 = -1;
    if (cem != -1 && rom != -1) {
        option2 = sumCandidate - cem + rom;
    }
    
    long long best = max(option1, option2);
    return best;
    }
};
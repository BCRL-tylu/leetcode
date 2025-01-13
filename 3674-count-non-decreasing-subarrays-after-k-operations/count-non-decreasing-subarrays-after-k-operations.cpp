#define ll long long int

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        stack<int> stack; // Stack to maintain indices
        vector<int> nextGreaterIndex(n, n); // Stores the next greater index for each element, initialized to n
        
        // Calculate next greater index (NGI) for each element in the array
        for (int i = 0; i < n; i++) {
            while (!stack.empty() && nums[i] > nums[stack.top()]) {
                nextGreaterIndex[stack.top()] = i; // Update NGI for the top index in the stack
                stack.pop();
            }
            stack.push(i); // Push the current index onto the stack
        }
        
        int left = 0; // Start index of the current valid subarray
        ll answer = 0; // Total count of valid subarrays
        int ma = nums[left]; // Current largest value in the subarray
        ll toadd = 0; // Difference sum between the largest and current elements in the subarray

        // Iterate through the array
        for (int right = 0; right < n; right++) {
            if (nums[right] > ma) {
                ma = nums[right]; // Update the largest value if a greater value is found
            } else {
                toadd += ma - nums[right]; // Accumulate the difference in toadd
            }

            // If toadd exceeds k, adjust the window
            while (toadd > k) {
                answer += right - left; // Add the count of valid subarrays ending at `right - 1`

                // Shift the start index of the subarray while maintaining validity
                if (nums[left + 1] >= nums[left]) {
                    left++;
                } else {
                    // Adjust for next greater index transitions
                    ll prevValue = nums[left];
                    ll prevIndex = left;
                    ll curValue = nums[left + 1];
                    ll curIndex = left + 1;
                    ma = curValue;

                    while (nextGreaterIndex[curIndex] <= right && nextGreaterIndex[prevIndex] != nextGreaterIndex[curIndex]) {
                        toadd -= (prevValue - curValue) * (nextGreaterIndex[curIndex] - curIndex); // Update toadd
                        curIndex = nextGreaterIndex[curIndex];
                        curValue = nums[curIndex];
                        ma = curValue;
                    }

                    if (right >= nextGreaterIndex[curIndex] && nextGreaterIndex[prevIndex] == nextGreaterIndex[curIndex]) {
                        toadd -= (prevValue - curValue) * (nextGreaterIndex[curIndex] - curIndex);
                        ma = nums[nextGreaterIndex[curIndex]];
                        curValue = ma;
                        curIndex = nextGreaterIndex[curIndex];
                        prevValue = curValue;
                        prevIndex = curIndex;

                        while (right >= nextGreaterIndex[curIndex] && nextGreaterIndex[prevIndex] == nextGreaterIndex[curIndex]) {
                            ma = nums[nextGreaterIndex[curIndex]];
                            curIndex = nextGreaterIndex[curIndex];
                            prevValue = curValue;
                            prevIndex = curIndex;
                        }
                    } else {
                        toadd -= (prevValue - curValue) * (right - curIndex + 1);
                    }
                    left++;
                }
            }
        }

        // Add remaining valid subarrays
        answer += 1ll * (n - left) * (n - left + 1) / 2;

        return answer;
    }
};

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    unordered_map<long long, int> memo;
    int n;
    
    int dp(int i, bool haveCarry, int carry, vector<int>& nums) {
        long long key = ((long long)i << 33) | ((long long)carry << 1) | (haveCarry ? 1LL : 0LL);
        if (memo.find(key) != memo.end())
            return memo[key];

        // No carried element: process the next three elements.
        if (!haveCarry) {
            if (i >= n) return 0; // No elements left.
            if (i == n - 1) return nums[i]; // One element left.
            if (i == n - 2) return max(nums[i], nums[i+1]); // Two elements: cost is their max.
            
            int a = nums[i], b = nums[i+1], c = nums[i+2];
            int arr[3] = {a, b, c};
            sort(arr, arr+3);

            // Option 1: Remove two smallest, cost = mid, carry forward the largest.
            int opt1 = arr[1] + dp(i+3, true, arr[2], nums);
            // Option 2: Remove two largest, cost = max, carry forward the smallest.
            int opt2 = arr[2] + dp(i+3, true, arr[0], nums);
            return memo[key] = min(opt1, opt2);
        } else {
            // Have a carried element, process it with the next two elements.
            if (i >= n) return carry; // Only the carry remains.
            if (i == n - 1) return max(carry, nums[i]); // Two elements left.

            int a = carry, b = nums[i], c = nums[i+1];
            int arr[3] = {a, b, c};
            sort(arr, arr+3);

            // Option 1: Remove two smallest, cost = mid, carry forward the largest.
            int opt1 = arr[1] + dp(i+2, true, arr[2], nums);
            // Option 2: Remove two largest, cost = max, carry forward the smallest.
            int opt2 = arr[2] + dp(i+2, true, arr[0], nums);
            return memo[key] = min(opt1, opt2);
        }
    }

    int minCost(vector<int>& nums) {
        n = nums.size();
        memo.clear();
        return dp(0, false, 0, nums);
    }
};

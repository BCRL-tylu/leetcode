class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1000000007;
        long long evenCount = 1, oddCount = 0;
        long long prefix = 0, result = 0;
        for (int num : arr) {
            prefix += num;
            // Check the parity of the current prefix sum.
            if (prefix % 2 == 0) {
                // If prefix is even, then any previous odd prefix gives an odd subarray.
                result = (result + oddCount) % MOD;
                evenCount++; 
            } else {
                // If prefix is odd, then any previous even prefix gives an odd subarray.
                result = (result + evenCount) % MOD;
                oddCount++;
            }
        }
        return result;
    }
};

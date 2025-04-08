class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        if (abs(k) > 900) return -1;
        
        // dp[parity][product] is a vector of bitsets.
        // Each bitset has 1801 bits to represent alternating sum states in range [-900, 900] (offset by 900).
        // The first index (parity) indicates the parity of the current subsequence:
        //   0: even length subsequence,
        //   1: odd length subsequence.
        // The second index is the current product of the subsequence.

        vector<vector<bitset<1801>>> dp(2, vector<bitset<1801>>(limit + 1));
        
        // The "any" DP tracks branches that are rescued (multiplication by 0) even if no valid product > 0 is achieved.
        // It has a second dimension of size 2:
        //   index 0: not rescued (normal branch),
        //   index 1: rescued branch (i.e. product is effectively 0).

        vector<vector<bitset<1801>>> any(2, vector<bitset<1801>>(2));
        
        // Initialization:
        // dp[0][1][900] is set to true: This represents the "empty" starting state (even parity, product = 1)
        // with an alternating sum of 0 (index 900 = 0+900). (Note: product 1 is like the identity for multiplication.)

        dp[0][1][900] = 1;
        
        // any[0][0][900] is set to true: Similar initialization for the "any" DP where we have not rescued yet.
        any[0][0][900] = 1;
        
        // Temporary bitset used for shifting intermediate states.
        bitset<1801> tmp;
        
        // Process each number in the input sequence.
        for (int i : nums) {
            // --- Update dp for normal multiplication ---
            // Loop over potential product values from current dp states, going in descending order.
            // We iterate over product values j so that when we do multiplication, we do not use updated values in the same iteration.
            if(i!=0) int templimt = limit/i;
            for (int j = limit; j >= 0; j--) {
                // If multiplying the current product j by the current number i exceeds the limit,
                // then skip this product state; it cannot be extended.
                if (j * i > limit) continue;
                
                // Save current dp state of parity 0 for product j into tmp.
                tmp = dp[0][j];
                
                // Extend branches that were at odd parity (dp[1][j]) by adding the current number
                // such that the new alternating sum becomes: oldSum - i (i.e. shift right by i).
                // And store the new state in dp[0][j * i] since parity flips (odd -> even).
                dp[0][j * i] |= dp[1][j] >> i;
                
                // Extend branches from parity 0 (stored in tmp) by adding the current number
                // so that the new alternating sum becomes: oldSum + i (i.e. shift left by i).
                // And store the new state in dp[1][j * i] (even -> odd).
                dp[1][j * i] |= tmp << i;
            }
            
            // --- Update the 'any' table for rescued states (multiplication by 0) ---
            // This loop is similar to the dp update loop but works on the boolean rescued tracking.
            // The second index in 'any' indicates whether the branch has been rescued (or will be).
            // Iterate over both possible boolean flags: 1 (rescued) and 0 (not rescued).
            for (int j = 1; j >= 0; j--) {
                // Save the current state of any[0][j] into tmp.
                tmp = any[0][j];
                
                // For branches currently in parity 1 (odd parity), apply a right shift by i
                // to simulate subtracting i from the alternating sum.
                // Then update the state for parity 0 in 'any'. The rescued flag becomes (j || i == 0)
                // meaning: if already rescued (j == 1) or the current number i is 0 (which rescues the branch).
                any[0][j || i == 0] |= any[1][j] >> i;
                
                // Similarly, for branches from parity 0, apply a left shift by i
                // (i.e. adding i) and update the state for parity 1.
                any[1][j || i == 0] |= tmp << i;
            }
        }
        
        // --- Answer extraction ---
        // We need to find the maximum product that yields an alternating sum of k.
        // The alternating sum state k corresponds to index 900+k due to our offset.
        int res = -1;
        // Iterate over product values in descending order from limit down to 1.
        for (int x = limit; x >= 1; x--) {
            // Check if either parity in dp with product 'x' can achieve an alternating sum of k.
            if (dp[0][x][900 + k] || dp[1][x][900 + k]) {
                // Special handling: if k==0 and the candidate product is 1, then a subsequence
                // composed entirely of 1's (with at least two 1's) may be intended.
                if (k == 0 && x == 1) {
                    int ones = 0;
                    for (int i : nums)
                        if (i == 1) ones++;
                    if (ones >= 2) return 1; 
                } else {
                    return x;
                }
            }
        }
        // If no normal product (>=1) was found, check in the 'any' DP table to see if
        // there is any rescued branch (product reset to 0) that achieves the alternating sum k.
        if (any[0][1][900 + k] || any[1][1][900 + k])
            return 0;
            
        // If neither a normal product nor a rescued branch exists, return -1.
        return -1;
    }
};

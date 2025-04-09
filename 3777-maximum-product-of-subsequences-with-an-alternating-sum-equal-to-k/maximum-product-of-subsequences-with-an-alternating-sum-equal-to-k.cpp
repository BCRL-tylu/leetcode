class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        if (abs(k) > 900) return -1;
        // we can have maximumum 900 and worst case -900 and 0, so total 1801 states
        //dp[1][j]: subsequences that currently have an odd length with product j
        //dp[0][j]: subsequences that currently have an even length with product j
        // each is stored as bitset set represent the alternating sums of the subsequences
        vector<vector<bitset<1801>>> dp(2, vector<bitset<1801>>(limit + 1));
        
        vector<vector<bitset<1801>>> any(2, vector<bitset<1801>>(2));
        dp[0][1][900] = any[0][0][900] = 1;// set 0 to 1
        bitset<1801> tmp;
        for (int i : nums) {
            for (int j = limit; j >= 0; j--) {
                if (j * i > limit) continue;
                tmp = dp[0][j];
                //dp[1][j]: subsequences(whose alteranting sum represnted by bitsets) that currently have an odd length (parity 1) and a product equal to j.
                //this operation is equivalent to reduce odd alternating sum all by i and dp[0][j] >> i = dp[1][j] -i, and 
                dp[0][j * i] |= dp[1][j] >> i;
                //this operation is equivalent to add even alternating sum all by i and dp[1][j] >> i = dp[0][j] + i for all possible subsequence
                dp[1][j * i] |= tmp << i;
            }
            // handle 0 products
            // if i ==0 any[0][1] = any[1][j] >> i
            // if i!=0 and j==0 - j length 1, then it's any[0][0]
            for (int j = 1; j >= 0; j--) {
                tmp = any[0][j];
                any[0][j || i == 0] |= any[1][j] >> i;
                any[1][j || i == 0] |= tmp << i;
            }
        }
        int res = -1;
        //scan all possible product values
        for (int x = limit; x >= 1; x--) {
            //if such product value x exist for either odd or even subsequence with latenrating sum k
            if (dp[0][x][900 + k] || dp[1][x][900 + k]) {
                //special judge if k ==0. and the the product equals 1
                if (k==0 && x==1) {
                    int ones=0;
                    for (int i : nums) if (i == 1) ones++;
                    // if at least 2 1s, we can constcuture 1 1 with alterating sum 0 and product 1, so we can return 1
                    if (ones>=2) return 1;
                } else {
                    return x;
                }
            }
        }
        if (any[0][1][900 + k] || any[1][1][900 + k]) return 0;
        return -1;
    }
};

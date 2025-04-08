class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        if (abs(k) > 900) return -1;
        vector<vector<bitset<1801>>> dp(2, vector<bitset<1801>>(limit + 1));
        vector<vector<bitset<1801>>> any(2, vector<bitset<1801>>(2));
        dp[0][1][900] = any[0][0][900] = 1;
        bitset<1801> tmp;
        for (int i : nums) {
            for (int j = limit; j >= 0; j--) {
                if (j * i > limit) continue;
                tmp = dp[0][j];
                dp[0][j * i] |= dp[1][j] >> i;
                dp[1][j * i] |= tmp << i;
            }
            for (int j = 1; j >= 0; j--) {
                tmp = any[0][j];
                any[0][j || i == 0] |= any[1][j] >> i;
                any[1][j || i == 0] |= tmp << i;
            }
        }
        int res = -1;
        for (int x = limit; x >= 1; x--) {
            if (dp[0][x][900 + k] || dp[1][x][900 + k]) {
                if (k == 0 && x == 1) {
                    int ones = 0;
                    for (int i : nums) if (i == 1) ones++;
                    if (ones >= 2) return 1;
                } else {
                    return x;
                }
            }
        }
        if (any[0][1][900 + k] || any[1][1][900 + k]) return 0;
        return -1;
    }
};
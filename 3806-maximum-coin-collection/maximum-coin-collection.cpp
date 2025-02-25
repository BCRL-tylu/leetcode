class Solution {
public:
    long long maxCoins(vector<int>& lane1, vector<int>& lane2) {
        vector<vector<long long>> dp(2, vector<long long>(3, LONG_LONG_MIN));
        const int n = lane1.size();
        long long r = LONG_LONG_MIN;
        for (int i = 0; i < n; ++i) {
            vector<vector<long long>> temp(2, vector<long long>(3, LONG_LONG_MIN));
            temp[0][0] = lane1[i];
            temp[1][1] = lane2[i];
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (dp[j][k] == LONG_LONG_MIN) continue;
                    const int t = k + (j != 0);
                    if (t < 3) {
                        temp[0][t] = max(temp[0][t], dp[j][k] + lane1[i]);
                    }
                }
            }
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (dp[j][k] == LONG_LONG_MIN) continue;
                    const int t = k + (j != 1);
                    if (t < 3) {
                        temp[1][t] = max(temp[1][t], dp[j][k] + lane2[i]);
                    }
                }
            }
            swap(dp, temp);
            r = max(r, *max_element(dp[0].begin(), dp[0].end()));
            r = max(r, *max_element(dp[1].begin(), dp[1].end()));
        }
        return r;
    }
};
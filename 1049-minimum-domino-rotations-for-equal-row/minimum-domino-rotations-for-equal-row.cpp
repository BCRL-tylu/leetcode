class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int n = tops.size();
         vector<int> dp(4, 0);
        int top = tops[0], bot = bottoms[0];

        bool topTopsOK = true, topBotsOK = true;
        bool botBotsOK = true, botTopsOK = true;

        // Scenario 0: make all tops == top
        for (int i = 0; i < n; i++) {
            if (tops[i] == top) {
                continue;
            } else if (bottoms[i] == top) {
                dp[0]++;
            } else {
                topTopsOK = false;
                break;
            }
        }

        // Scenario 1: make all bottoms == top
        for (int i = 0; i < n; i++) {
            if (bottoms[i] == top) {
                continue;
            } else if (tops[i] == top) {
                dp[1]++;
            } else {
                topBotsOK = false;
                break;
            }
        }

        // Scenario 2: make all bottoms == bot
        for (int i = 0; i < n; i++) {
            if (bottoms[i] == bot) {
                continue;
            } else if (tops[i] == bot) {
                dp[2]++;
            } else {
                botBotsOK = false;
                break;
            }
        }

        // Scenario 3: make all tops == bot
        for (int i = 0; i < n; i++) {
            if (tops[i] == bot) {
                continue;
            } else if (bottoms[i] == bot) {
                dp[3]++;
            } else {
                botTopsOK = false;
                break;
            }
        }

        int ans = INT_MAX;
        if (topTopsOK)  ans = min(ans, dp[0]);
        if (topBotsOK)  ans = min(ans, dp[1]);
        if (botBotsOK)  ans = min(ans, dp[2]);
        if (botTopsOK)  ans = min(ans, dp[3]);

        return (ans == INT_MAX ? -1 : ans);
    }
};
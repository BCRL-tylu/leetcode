#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits.h>

class Solution {
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs) {
        queue<pair<int, int>> day7;  // Queue for 7-day pass
        queue<pair<int, int>> day30; // Queue for 30-day pass
        int n = days.size();
        vector<int> dp(n + 1, 0);
        dp[0] = 0;

        for (int i = 0; i < n; ++i) {
            // Remove expired entries for 7-day pass
            while (!day7.empty() && day7.front().second < days[i]) {
                day7.pop();
            }
            int oneday = min(dp[i] + costs[0],dp[i] + costs[1]);
            oneday = min(oneday,dp[i] + costs[2]);

            if (!day7.empty()) {
                dp[i + 1] = min(oneday, dp[day7.front().first - 1] + costs[1]);
            } else {
                dp[i + 1] = oneday;
            }

            // Remove expired entries for 30-day pass
            while (!day30.empty() && day30.front().second < days[i]) {
                day30.pop();
            }
            if (!day30.empty()) {
                dp[i + 1] = min(dp[i + 1], dp[day30.front().first - 1] + costs[2]);
            } else {
                dp[i + 1] = min(oneday, dp[i + 1]);
            }

            // Push current day with valid range for 7-day and 30-day passes
            day7.push({i + 1, days[i] + 6});  // 7-day pass expires after 6 days
            day30.push({i + 1, days[i] + 29}); // 30-day pass expires after 29 days
        }

        return dp[n];  // Return minimum cost for all days
    }
};

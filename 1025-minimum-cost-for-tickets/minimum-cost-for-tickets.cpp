class Solution {
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs) {
        std::queue<std::pair<int, int>> day7;  // Queue for 7-day pass
        std::queue<std::pair<int, int>> day30; // Queue for 30-day pass
        int n = days.size();
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            // Remove expired entries for 7-day pass
            while (!day7.empty() && day7.front().second < days[i]) {
                day7.pop();
            }
            // Remove expired entries for 30-day pass
            while (!day30.empty() && day30.front().second < days[i]) {
                day30.pop();
            }
            // Calculate minimum cost for the current day
            int oneDayCost = dp[i] + costs[0];
            int sevenDayCost = (!day7.empty()) ? dp[day7.front().first - 1] + costs[1] : dp[i] + costs[1];
            int thirtyDayCost = (!day30.empty()) ? dp[day30.front().first - 1] + costs[2] :dp[i] + costs[2];
            dp[i + 1] = std::min({oneDayCost, sevenDayCost, thirtyDayCost});
            // Add the current day to the queues for 7-day and 30-day passes
            day7.push({i + 1, days[i] + 6});
            day30.push({i + 1, days[i] + 29});
        }
        return dp[n];
    }
};

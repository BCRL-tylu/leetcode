class Solution {
public:
    long long maxCoins(vector<int>& lane1, vector<int>& lane2) {
        int n = lane1.size();
        const long long NEG_INF = -1e18;
        
        // dp0, dp1, dp2 represent our three states for each mile i.
        // dp0 -stay on line 1
        // dp1 - Switch line once
        // dp2 - switch line twice
        vector<long long> dp0(n, NEG_INF), dp1(n, NEG_INF), dp2(n, NEG_INF);
        
        // Base case: at mile 0.
        dp0[0] = lane1[0]; 
        dp1[0] = lane2[0];
        long long ans = max(dp0[0], dp1[0]);
        for (int i = 1; i < n; i++) {
            // Stay in lane 1
            dp0[i] = max((long long)lane1[i], dp0[i-1] + lane1[i]);
             // Switch from lane 1 to lane 2 or stay in lane 2
            dp1[i] = max({ (long long)lane2[i], dp1[i-1] + lane2[i], dp0[i-1] + lane2[i] });
            // Switch from lane 2 back to lane 1 or stay in lane 1
            dp2[i] = max(dp2[i-1] + lane1[i], dp1[i-1] + lane1[i]);

            ans = max({ans, dp0[i], dp1[i], dp2[i] });
        }
        return ans;
    }
};

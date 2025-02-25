class Solution {
public:
    long long maxCoins(vector<int>& lane1, vector<int>& lane2) {
        int n = lane1.size();
        // Use a very small number as -infinity.
        const long long NEG_INF = -1e18;
        
        // dp0, dp1, dp2 represent our three states for each mile i.
        vector<long long> dp0(n, NEG_INF), dp1(n, NEG_INF), dp2(n, NEG_INF);
        
        // Base case: at mile 0.
        dp0[0] = lane1[0];     // Start on lane1 without any switch.
        dp1[0] = lane2[0];     // Allowed: switch immediately upon entering.
        // dp2[0] remains -infinity because two switches at mile 0 is impossible.
        
        long long ans = max(dp0[0], dp1[0]);
        
        for (int i = 1; i < n; i++) {
            // Either start fresh at mile i or extend the previous segment.
            dp0[i] = max((long long)lane1[i], dp0[i-1] + lane1[i]);
            dp1[i] = max({ (long long)lane2[i], dp1[i-1] + lane2[i], dp0[i-1] + lane2[i] });
            dp2[i] = max(dp2[i-1] + lane1[i], dp1[i-1] + lane1[i]);
            
            ans = max({ ans, dp0[i], dp1[i], dp2[i] });
        }
        
        return ans;
    }
};

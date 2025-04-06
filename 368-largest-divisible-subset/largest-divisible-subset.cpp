class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return {};
        
        vector<pair<int,int>> qws;
        for(int i = 0; i < n; i++){
            qws.push_back({nums[i], i});
        }
        sort(qws.begin(), qws.end());
        
        vector<vector<pair<int,int>>> dp(n);
        dp[0].push_back(qws[0]);
        
        for (int i = 1; i < n; i++){
            vector<pair<int,int>> best;
            for (int j = 0; j < i; j++){
                if(qws[i].first % qws[j].first == 0 && dp[j].size() > best.size()){
                    best = dp[j];
                }
            }
            dp[i] = best;
            dp[i].push_back(qws[i]);
        }

        vector<pair<int,int>> bestChain;
        for (int i = 0; i < n; i++){
            if(dp[i].size() > bestChain.size())
                bestChain = dp[i];
        }
        
        vector<int> ans;
        for(auto &p : bestChain){
            ans.push_back(p.first);
        }
        return ans;
    }
};

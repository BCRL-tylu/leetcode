class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size();
        vector<vector<vector<int>>> adj(n+1);
        for(auto &e: edges){
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        vector<vector<long long>> dp(n+1, vector<long long>(2));
        auto dfs = [&](auto&& self, int node, int par) -> void{
            /*
            x = {a, b, c}
            dp[a][0] = not take
            dp[a][1] = take + cost
            if(dp[a][0] >= dp[a][1] + cost) not take
            */  
            // it will have sum for all nottake
            long long sum = 0;
            // for all takes
            vector<int> val;
            for(auto &c: adj[node]){
                if(c[0] != par){
                    self(self, c[0], node);
                    sum += dp[c[0]][0];
                    val.push_back(dp[c[0]][1] + c[1] - dp[c[0]][0]);
                }
            }
            sort(val.begin(), val.end());
            // now maximize k-1 and k
            int n = val.size();
            int cnt = 0;
            for(int i=0; i<n && cnt < (k-1); i++){
                if(val.back() > 0){
                    sum += val.back();
                    cnt++;
                }
                val.pop_back();
            }
            dp[node][1] = sum;
            while(val.size()){
                if(val.back() > 0){
                    sum += val.back();
                    break;
                }
                val.pop_back();
            }
            dp[node][0] = sum; 
        };
        dfs(dfs, 0, -1);
        return max(dp[0][0], dp[0][1]);
    }
};
class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = amount.size();
        vector<vector<int>> adj(n);
        for(auto& e : edges){
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        // Build parent and depth info from root 0.
        vector<int> parent(n, -1), depth(n, 0);
        function<void(int, int)> dfsBuild = [&](int node, int par) {
            parent[node] = par;
            for (int nxt : adj[node]) {
                if(nxt == par) continue;
                depth[nxt] = depth[node] + 1;
                dfsBuild(nxt, node);
            }
        };
        dfsBuild(0, -1);
        
        // Compute the time Bob visits each node on his unique path from bob to root.
        const int INF = 1e9;
        vector<int> bobTime(n, INF);
        int t = 0, cur = bob;
        while(cur != -1) {
            bobTime[cur] = t;
            cur = parent[cur];
            t++;
        }
        
        int ans = -1e9;
        // DFS for Alice from the root. At time t, if Alice is at node,
        // her contribution is decided by comparing t with bobTime[node]:
        // - If t < bobTime[node]: she gets full amount[node]
        // - If t == bobTime[node]: she gets half of amount[node]
        // - If t > bobTime[node]: Bob already opened the gate, so she gets 0.
        function<void(int, int, int)> dfsAlice = [&](int node, int t, int income) {
            int currIncome = income;
            if(t < bobTime[node])
                currIncome += amount[node];
            else if(t == bobTime[node])
                currIncome += amount[node] / 2;
            // Otherwise, Bob reached earlier so no money is added.
            
            // Check if node is a leaf (except for the root which might be a singleton)
            bool isLeaf = true;
            for (int nxt : adj[node]) {
                if(nxt == parent[node]) continue;
                isLeaf = false;
                dfsAlice(nxt, t + 1, currIncome);
            }
            if(isLeaf)
                ans = max(ans, currIncome);
        };
        
        dfsAlice(0, 0, 0);
        return ans;
    }
};

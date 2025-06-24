class Solution {
public:
    int minIncrease(int N, vector<vector<int>>& edges, vector<int>& cost) {
        // 1) 建树 (root = 0)
        vector<vector<int>> adj(N), children(N);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<int> parent(N, -1);
        parent[0] = 0;
        stack<int> st;
        st.push(0);
        while (!st.empty()) {
            int u = st.top(); st.pop();
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                children[u].push_back(v);
                st.push(v);
            }
        }
        
        // 2) dfs1: 计算 pathSum[u] 并更新 target = max(leaf path sum)
        vector<long long> pathSum(N);
        long long target = 0;
        function<void(int,long long)> dfs1 = [&](int u, long long acc) {
            pathSum[u] = acc + cost[u];
            if (children[u].empty()) {
                target = max(target, pathSum[u]);
            }
            for (int v : children[u]) {
                dfs1(v, pathSum[u]);
            }
        };
        dfs1(0, 0);
        
        // 3) dfs2: 后序计算 Rmin[u]
        //    Rmin[u] = 子树叶子中最小 (target - pathSum[leaf])
        const long long INF = LLONG_MAX / 4;
        vector<long long> Rmin(N, INF);
        function<long long(int)> dfs2 = [&](int u) -> long long {
            if (children[u].empty()) {
                return Rmin[u] = target - pathSum[u];
            }
            long long mn = INF;
            for (int v : children[u]) {
                mn = min(mn, dfs2(v));
            }
            return Rmin[u] = mn;
        };
        dfs2(0);
        
        // 4) dfs3: 前序贪心，把增量优先放高层
        int answer = 0;
        function<void(int,long long)> dfs3 = [&](int u, long long res) {
            long long need = Rmin[u] - res;
            if (need > 0) {
                ++answer;
                res += need;
            }
            for (int v : children[u]) {
                dfs3(v, res);
            }
        };
        dfs3(0, 0);
        
        return answer;
    }
};

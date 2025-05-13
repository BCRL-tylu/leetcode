class Solution {
public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        vector<char> seen(n);
        vector<vector<int>> comps;
        vector<int> sz, ed;
        vector<char> cyc;
        for (int i = 0; i < n; i++) if (!seen[i]) {
            vector<int> q = {i};
            seen[i] = 1;
            int cnt = 0;
            for (int j = 0; j < q.size(); j++) {
                int u = q[j];
                cnt += g[u].size();
                for (int v : g[u]) if (!seen[v]) {
                    seen[v] = 1;
                    q.push_back(v);
                }
            }
            comps.push_back(q);
            ed.push_back(cnt/2);
            sz.push_back(q.size());
            cyc.push_back(cnt/2 == q.size());
        }
        int m = comps.size();
        vector<int> o(m);
        iota(o.begin(), o.end(), 0);
        sort(o.begin(), o.end(), [&](int a, int b) {
            long lhs = 1L*ed[a]*sz[b], rhs = 1L*ed[b]*sz[a];
            if (lhs != rhs) return lhs > rhs;
            return sz[a] > sz[b];
        });
        vector<long long> val(n);
        long long cur = n;
        for (int id : o) {
            auto &q = comps[id];
            int c = sz[id];
            vector<long long> S(c), P;
            for (int i = 0; i < c; i++) S[i] = cur - c + 1 + i;
        
                for (int i = 1; i < c; i += 2) P.push_back(S[i]);
                int st = ((c-1)%2==0 ? c-1 : c-2);
                for (int i = st; i >= 0; i -= 2) P.push_back(S[i]);
            
            vector<int> tour;
            if (cyc[id]) {
                int s = q[0], u = s, p = -1;
                do {
                    tour.push_back(u);
                    int v = (g[u][0]==p ? g[u][1] : g[u][0]);
                    p = u; u = v;
                } while (u != s);
            } else {
                int u = q[0], p = -1;
                for (int v : q) if (g[v].size()<2) { u = v; break; }
                while (1) {
                    tour.push_back(u);
                    int v2 = -1;
                    for (int v : g[u]) if (v != p) { v2 = v; break; }
                    if (v2<0) break;
                    p = u; u = v2;
                }
            }
            for (int i = 0; i < c; i++) val[tour[i]] = P[i];
            cur -= c;
        }
        long long ans = 0;
        for (auto &e : edges) ans += val[e[0]] * val[e[1]];
        return ans;
    }
};

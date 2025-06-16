#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<pair<int,int>>> adj;
    vector<int> depth;
    vector<long long> distRoot;
    vector<vector<int>> parent;
    vector<vector<long long>> distUp;
    int N, LOG;

    void dfs(int u, int p, int d, long long dist) {
        parent[0][u] = p;
        depth[u] = d;
        distRoot[u] = dist;
        for (auto &e : adj[u]) {
            int v = e.first, w = e.second;
            if (v == p) continue;
            distUp[0][v] = w;
            dfs(v, u, d+1, dist + w);
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int k = 0; k < LOG; k++) {
            if (diff & (1<<k)) {
                u = parent[k][u];
            }
        }
        if (u == v) return u;
        for (int k = LOG-1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    // Climb from x upwards until just before accumulating ≥ rem
    // Returns the node whose parent is the first node at or past rem.
    int climbUntil(long long rem, int x) {
        for (int k = LOG-1; k >= 0; k--) {
            int anc = parent[k][x];
            if (anc != -1 && distUp[k][x] < rem) {
                rem -= distUp[k][x];
                x = anc;
            }
        }
        // one more step to cross the threshold
        return parent[0][x];
    }

    // Climb from x upwards consuming up to rem total weight, 
    // stopping at the deepest node whose distance->x ≤ rem
    int climbAtMost(long long rem, int x) {
        for (int k = LOG-1; k >= 0; k--) {
            int anc = parent[k][x];
            if (anc != -1 && distUp[k][x] <= rem) {
                rem -= distUp[k][x];
                x = anc;
            }
        }
        return x;
    }

    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        N = n;
        adj.assign(N, {});
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }

        // compute LOG = ⌈log2(N)⌉+1
        LOG = 1;
        while ((1<<LOG) <= N) LOG++;
        parent.assign(LOG, vector<int>(N, -1));
        distUp.assign(LOG, vector<long long>(N, 0));
        depth.assign(N, 0);
        distRoot.assign(N, 0);

        // root at 0
        dfs(0, -1, 0, 0LL);

        // build binary‑lifting tables
        for (int k = 1; k < LOG; k++) {
            for (int v = 0; v < N; v++) {
                int p = parent[k-1][v];
                if (p < 0) {
                    parent[k][v] = -1;
                    distUp[k][v] = distUp[k-1][v];
                } else {
                    parent[k][v]    = parent[k-1][p];
                    distUp[k][v]    = distUp[k-1][v] + distUp[k-1][p];
                }
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                ans.push_back(u);
                continue;
            }
            int L = lca(u, v);
            long long totalDist = distRoot[u] + distRoot[v] - 2*distRoot[L];
            long long half = (totalDist + 1) / 2;  // ceil(totalDist/2)

            long long du = distRoot[u] - distRoot[L];
            if (half <= du) {
                // median lies on the u→L path
                ans.push_back(climbUntil(half, u));
            } else {
                // median on the L→v path
                long long rem2 = half - du;         // distance past L
                long long dv = distRoot[v] - distRoot[L];
                long long K  = dv - rem2;           // distance from v to median
                ans.push_back(climbAtMost(K, v));
            }
        }

        return ans;
    }
};

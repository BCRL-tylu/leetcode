#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1,
                               vector<vector<int>>& edges2,
                               int k) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        // build adjacency lists
        vector<vector<int>> adj1(n), adj2(m);
        for (auto &e : edges1) {
            int u = e[0], v = e[1];
            adj1[u].push_back(v);
            adj1[v].push_back(u);
        }
        for (auto &e : edges2) {
            int u = e[0], v = e[1];
            adj2[u].push_back(v);
            adj2[v].push_back(u);
        }

        // g1[i] = # nodes in tree1 within distance ≤ k of i
        // g2[j] = # nodes in tree2 within distance ≤ k−1 of j
        auto g1 = computeWithinDist(n, adj1, k);
        auto g2 = computeWithinDist(m, adj2, k-1);

        // best you can do in tree2 by choosing the best attach-point
        int M = 0;
        if (k > 0) 
            M = *max_element(g2.begin(), g2.end());

        // answer[i] = g1[i] + M
        vector<int> answer(n);
        for (int i = 0; i < n; i++) {
            answer[i] = g1[i] + M;
        }
        return answer;
    }

private:
    struct Info { int c, dist, comp; };

    // Returns for each u in [0..N-1], the count of nodes within distance ≤ R of u.
    // Runs in O(N log²N) via centroid decomposition.
    vector<int> computeWithinDist(int N,
                                  const vector<vector<int>>& adj,
                                  int R) {
        vector<bool> blocked(N, false);
        vector<int>  subSize(N, 0), centroidParent(N, -1);
        vector<vector<Info>>                  layers(N);
        vector<vector<int>>                   allDist(N);
        vector<vector<vector<int>>>           childDist(N);

        // 1) compute subtree sizes
        auto dfsSize = [&](auto&& self, int u, int p) -> void {
            subSize[u] = 1;
            for (int v : adj[u]) if (!blocked[v] && v != p) {
                self(self, v, u);
                subSize[u] += subSize[v];
            }
        };

        // 2) find centroid of a component of size sz rooted at u
        auto findCentroid = [&](auto&& self, int u, int p, int sz) -> int {
            for (int v : adj[u]) if (!blocked[v] && v != p
                                     && subSize[v] * 2 > sz)
                return self(self, v, u, sz);
            return u;
        };

        // 3) gather distances from centroid c into its component
        auto dfsDist = [&](auto&& self,
                           int u, int p, int d, int c, int comp) -> void {
            layers[u].push_back({c, d, comp});
            allDist[c].push_back(d);
            if (comp >= 0)
                childDist[c][comp].push_back(d);
            for (int v : adj[u]) if (!blocked[v] && v != p) {
                self(self, v, u, d + 1, c, comp);
            }
        };

        // 4) build the centroid‐decomposition
        auto decompose = [&](auto&& self, int entry, int p) -> void {
            dfsSize(dfsSize, entry, -1);
            int c = findCentroid(findCentroid, entry, -1, subSize[entry]);

            blocked[c]         = true;
            centroidParent[c]  = p;

            // record centroid -> itself
            layers[c].push_back({c, 0, -1});
            allDist[c].push_back(0);

            // count how many child‐subtrees remain
            int comps = 0;
            for (int v : adj[c]) if (!blocked[v]) comps++;
            childDist[c].assign(comps, {});

            // gather distances in each child‐subtree
            int idx = 0;
            for (int v : adj[c]) if (!blocked[v]) {
                dfsDist(dfsDist, v, c, 1, c, idx);
                idx++;
            }

            // sort for binary‐search
            sort(allDist[c].begin(), allDist[c].end());
            for (int i = 0; i < comps; i++)
                sort(childDist[c][i].begin(), childDist[c][i].end());

            // recurse on each subtree
            for (int v : adj[c]) if (!blocked[v])
                self(self, v, c);
        };

        // start decomposition from node 0
        decompose(decompose, 0, -1);

        // now answer the “ball of radius R” query for every u
        vector<int> cnt(N, 0);
        for (int u = 0; u < N; u++) {
            long long reached = 0;
            for (auto &info : layers[u]) {
                int c    = info.c;
                int du   = info.dist;
                int comp = info.comp;
                int rem  = R - du;
                if (rem < 0) continue;

                // total in centroid c’s component within rem
                auto &A = allDist[c];
                long long tot = upper_bound(A.begin(), A.end(), rem)
                              - A.begin();

                // subtract the child‐subtree that contains u
                if (comp >= 0) {
                    auto &B = childDist[c][comp];
                    tot -= upper_bound(B.begin(), B.end(), rem)
                         - B.begin();
                }
                reached += tot;
            }
            cnt[u] = (int)reached;
        }

        return cnt;
    }
};

#include <bits/stdc++.h>
using namespace std;

struct Edge { int u, v; };
using VI  = vector<int>;
using VVI = vector<VI>;

class Solution {
public:
    vector<int> maxTargetNodes(const VVI& edges1,
                               const VVI& edges2,
                               int k) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        // build adjacency
        VVI adj1(n), adj2(m);
        for (auto &e : edges1) {
            adj1[e[0]].push_back(e[1]);
            adj1[e[1]].push_back(e[0]);
        }
        for (auto &e : edges2) {
            adj2[e[0]].push_back(e[1]);
            adj2[e[1]].push_back(e[0]);
        }

        // compute g1, g2 in O(n log n) and O(m log m)
        auto g1 = withinDist(adj1, k);
        auto g2 = withinDist(adj2, max(0, k-1));

        // best we can cover in tree2
        int M = k>0 ? *max_element(g2.begin(), g2.end()) : 0;

        vector<int> ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = g1[i] + M;
        return ans;
    }

private:
    int N, R;
    const VVI *padj;
    vector<bool>      blocked;
    vector<int>       subSize, answer;
    
    // Decompose recursion
    void decompose(int root) {
        int sz = dfsSize(root, -1);
        int c  = findCentroid(root, -1, sz);
        blocked[c] = true;

        // gather (node, dist, compIdx)
        vector<tuple<int,int,int>> rec;
        rec.reserve(sz);

        // centroid itself
        rec.emplace_back(c, 0, -1);

        // for each child‐subtree assign compIdx and DFS
        int compCnt = 0;
        for (int v : (*padj)[c]) if (!blocked[v]) {
            dfsGather(v, c, 1, compCnt, rec);
            ++compCnt;
        }

        // figure maxDepth
        int maxD = 0;
        for (auto &t : rec)
            maxD = max(maxD, get<1>(t));

        // build freq and prefix
        vector<int> freq(maxD+1, 0);
        for (auto &t : rec)
            freq[get<1>(t)]++;
        for (int i = 1; i <= maxD; ++i)
            freq[i] += freq[i-1];

        // build per‐comp freq & prefix
        vector< vector<int> > compFreq(compCnt, vector<int>(maxD+1, 0));
        for (auto &t : rec) {
            int d = get<1>(t), ci = get<2>(t);
            if (ci >= 0) compFreq[ci][d]++;
        }
        for (int i = 0; i < compCnt; ++i)
            for (int d = 1; d <= maxD; ++d)
                compFreq[i][d] += compFreq[i][d-1];

        // now for each record add to answer[u]
        for (auto &t : rec) {
            int u = get<0>(t);
            int d = get<1>(t);
            int ci= get<2>(t);

            int rem = R - d;
            if (rem < 0) continue;
            rem = min(rem, maxD);

            int tot = freq[rem];
            if (ci >= 0) tot -= compFreq[ci][rem];
            answer[u] += tot;
        }

        // recurse on subtrees
        for (int v : (*padj)[c]) 
            if (!blocked[v]) 
                decompose(v);
    }

    // compute subSize
    int dfsSize(int u, int p) {
        subSize[u] = 1;
        for (int v : (*padj)[u]) 
            if (v!=p && !blocked[v]) 
                subSize[u] += dfsSize(v, u);
        return subSize[u];
    }

    // find centroid
    int findCentroid(int u, int p, int sz) {
        for (int v : (*padj)[u]) {
            if (v!=p && !blocked[v] && subSize[v]*2 > sz)
                return findCentroid(v, u, sz);
        }
        return u;
    }

    // gather (node, dist from c, compIdx)
    void dfsGather(int u, int p, int d, int comp, 
                   vector<tuple<int,int,int>>& rec) {
        rec.emplace_back(u, d, comp);
        for (int v : (*padj)[u]) {
            if (v!=p && !blocked[v])
                dfsGather(v, u, d+1, comp, rec);
        }
    }

    vector<int> withinDist(const VVI& adj, int RR) {
        padj    = &adj;
        N       = adj.size();
        R       = RR;
        blocked.assign(N, false);
        subSize.assign(N, 0);
        answer .assign(N, 0);
        decompose(0);
        return answer;
    }
};

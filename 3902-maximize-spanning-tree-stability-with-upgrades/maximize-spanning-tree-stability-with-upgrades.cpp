#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n), r(n,0) {
        for(int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        DSU dsu(n);
        int used = 0;

        for (auto &e : edges) if (e[3] == 1) {
            if (!dsu.unite(e[0], e[1])) 
                return -1;       // cycle among must-edges!
            used++;
        }

        priority_queue<pair<int,int>> pq;
        for (int i = 0; i < (int)edges.size(); i++) 
            if (edges[i][3] == 0) pq.push({edges[i][2], i});
        

        vector<int> chosen;
        while (used < n - 1 && !pq.empty()) {
            auto [w, i] = pq.top(); pq.pop();
            if (dsu.unite(edges[i][0], edges[i][1])) {
                chosen.push_back(i);
                used++;
            }
        }
        if (used < n - 1) return -1;

        sort(chosen.begin(), chosen.end(),
             [&](int a, int b){
               return edges[a][2] < edges[b][2];
             });
        for (int idx = 0; idx < k && idx < (int)chosen.size(); idx++) {
            int i = chosen[idx];
            edges[i][2] *= 2;
        }

        int stability = INT_MAX;
        for (auto &e : edges) 
            if (e[3] == 1)stability = min(stability, e[2]);
        
        for (int i : chosen) stability = min(stability, edges[i][2]);
        
        return stability;
    }
};

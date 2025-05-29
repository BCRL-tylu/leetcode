#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1,
                               vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        // build adjacency lists
        vector<vector<int>> adj1(n), adj2(m);
        for (auto &e : edges1) {
            adj1[e[0]].push_back(e[1]);
            adj1[e[1]].push_back(e[0]);
        }
        for (auto &e : edges2) {
            adj2[e[0]].push_back(e[1]);
            adj2[e[1]].push_back(e[0]);
        }

        // helper: BFS‐2-colour a tree, return {count0, count1}
        auto bfs_color = [&](const vector<vector<int>>& adj, vector<int>& color){
            int N = adj.size();
            color.assign(N, -1);
            queue<int> q;
            color[0] = 0;
            q.push(0);
            int cnt0 = 1, cnt1 = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (color[v] < 0) {
                        color[v] = color[u] ^ 1;
                        if (color[v] == 0) ++cnt0;
                        else              ++cnt1;
                        q.push(v);
                    }
                }
            }
            return make_pair(cnt0, cnt1);
        };

        vector<int> col1, col2;
        auto [n0, n1] = bfs_color(adj1, col1);
        auto [m0, m1] = bfs_color(adj2, col2);

        // best extra from Tree 2 is the larger opposite-colour class
        int B = max(m0, m1);

        // answer[i] = #same-colour in T1 + B
        vector<int> answer(n);
        for (int i = 0; i < n; i++) {
            int same = (col1[i] == 0 ? n0 : n1);
            answer[i] = same + B;
        }
        return answer;
    }
};

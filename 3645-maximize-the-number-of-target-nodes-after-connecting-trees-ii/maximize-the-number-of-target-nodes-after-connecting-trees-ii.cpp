#include <vector>
#include <stack>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

class Solution {
public:
    vi adj[100001];

    void color(const vvi &edges, vi &col, int &c0, int &c1) {
        int n = edges.size() + 1;
        // Clear the adjacency list and color vector
        for (int i = 0; i < n; i++) adj[i].clear();
        
        // Build the adjacency list
        for (const auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        col.assign(n, -1); // Initialize color vector to -1
        c0 = c1 = 0;

        // Iterative DFS for coloring
        stack<pair<int, int>> s; // (node, color)
        s.push({0, 0}); // Start with node 0 colored 0

        while (!s.empty()) {
            auto [x, val] = s.top();
            s.pop();
            if (col[x] != -1) continue; // Already colored
            
            col[x] = val;
            if (val == 0) c0++;
            else c1++;

            // Push neighbors with alternate color
            for (int y : adj[x]) {
                if (col[y] == -1) {
                    s.push({y, 1 - val}); // Alternate color
                }
            }
        }
    }

    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        vi a, b;
        int c0, c1, c2, c3;
        color(edges1, a, c0, c1);
        color(edges2, b, c2, c3);

        if (c2 < c3) swap(c2, c3); // Ensure c2 >= c3
        int n = a.size();
        vector<int> ret(n);

        // Compute the result based on the coloring
        for (int i = 0; i < n; i++) {
            ret[i] = (a[i] == 1 ? c1 : c0) + c2;
        }

        return ret;
    }
};

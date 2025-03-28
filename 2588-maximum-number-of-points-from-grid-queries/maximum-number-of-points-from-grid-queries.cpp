
using Node = tuple<int, int, int>;
using pq_t = priority_queue<Node, vector<Node>, greater<Node>>;

class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int m = grid.size(), n = grid[0].size();
        int k = queries.size();
        
        vector<pair<int, int>> sq;
        for (int i = 0; i < k; i++) {
            sq.emplace_back(queries[i], i);
        }
        sort(sq.begin(), sq.end());
        
        vector<int> ans(k, 0);
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        pq_t q;
        q.push({grid[0][0], 0, 0});
        visited[0][0] = true;
        
        int count = 0;
        vector<int> dr = {1, -1, 0, 0};
        vector<int> dc = {0, 0, 1, -1};

        for (auto [query, qi] : sq) {  // Renamed q to query
            while (!q.empty() && get<0>(q.top()) < query) {
                auto [val, r, c] = q.top();
                q.pop();
                count++; 
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n || visited[nr][nc]) continue;
                    visited[nr][nc] = true;
                    q.push({grid[nr][nc], nr, nc});
                }
            }
            ans[qi] = count;
        }
        return ans;
    }
};
class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int m = grid.size(), n = grid[0].size();
        int k = queries.size();
        
        // Pair each query with its original index and sort by the query value.
        vector<pair<int, int>> sortedQueries;
        for (int i = 0; i < k; i++) {
            sortedQueries.push_back({queries[i], i});
        }
        sort(sortedQueries.begin(), sortedQueries.end());
        
        vector<int> ans(k, 0);
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        // Priority queue: (grid value, row, col)
        // Using a min-heap so that we always expand the smallest cell value first.
        using Node = tuple<int, int, int>;
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        
        // Start from (0,0) if it hasn't been visited.
        pq.push({grid[0][0], 0, 0});
        visited[0][0] = true;
        
        int count = 0;  // number of cells visited (points)
        vector<int> dr = {1, -1, 0, 0};
        vector<int> dc = {0, 0, 1, -1};
        
        // Process queries in sorted order.
        for (auto [q, qi] : sortedQueries) {
            // Expand reachable region while the smallest cell in the PQ is valid for the current query.
            while (!pq.empty() && get<0>(pq.top()) < q) {
                auto [val, r, c] = pq.top();
                pq.pop();
                count++; // first time visiting this cell, so count one point.
                
                // Explore its 4 neighbors.
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n || visited[nr][nc])
                        continue;
                    visited[nr][nc] = true;
                    pq.push({grid[nr][nc], nr, nc});
                }
            }
            // After processing, assign the number of points obtained for this query.
            ans[qi] = count;
        }
        
        return ans;
    }
};

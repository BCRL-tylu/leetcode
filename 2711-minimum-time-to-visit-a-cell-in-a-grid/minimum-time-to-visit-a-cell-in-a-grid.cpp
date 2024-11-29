class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if (grid[0][1] > 1 && grid[1][0] > 1) return -1;
        int m = grid.size(), n = grid[0].size();
        int dist[m][n];
        memset(dist,10001,sizeof(dist));
        dist[0][0] = 0;
        // Priority queue: {distance, {row, col}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        pq.push({0, {0, 0}});
        // Directions: {right, down, left, up}
        int d[5] = {0, 1, 0, -1, 0};
        while (!pq.empty()) {
            auto [currentDist, cell] = pq.top();
            pq.pop();
            int x = cell.first, y = cell.second;
            // Early exit if we reached the destination
            if (x == m - 1 && y == n - 1) return currentDist;
            // Skip if already processed
            if (currentDist > dist[x][y]) continue;
            for (int i = 0; i < 4; ++i) {
                int nx = x + d[i], ny = y + d[i+1];
                if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                    int newdist = currentDist + 1;
                    int waitTime = max(0, grid[nx][ny] - newdist);
                    // Adjust to next valid time if waitTime is odd
                    if (waitTime % 2) ++waitTime;
                    int nextDist = newdist + waitTime;
                    if (nextDist < dist[nx][ny]) {
                        dist[nx][ny] = nextDist;
                        pq.push({nextDist, {nx, ny}});
                    }
                }
            }
        }
        return -1;
    }
};

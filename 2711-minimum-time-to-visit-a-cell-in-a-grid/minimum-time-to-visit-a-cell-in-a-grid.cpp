class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if (grid[0][1] > 1 && grid[1][0] > 1) return -1;
        int m = grid.size(), n = grid[0].size();
        int dist[m][n];
        memset(dist,10001,sizeof(dist));
        dist[0][0] = 0;

        int current[m][n];
        memset(current,-1,sizeof(dist));
        current[0][0] = 0;

        // Priority queue: {distance, {row, col}}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, 0});
        // Directions: {right, down, left, up}
        int d[5] = {0, 1, 0, -1, 0};
        while (!pq.empty()) {
            auto [x,y] = pq.top();
            int currentDist = current[x][y];
            pq.pop();
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
                        current[nx][ny] = nextDist;
                        pq.push({nx, ny});
                    }
                }
            }
        }
        return -1;
    }
};

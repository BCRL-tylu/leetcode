class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if(grid[0][1] > 1 && grid[1][0] > 1) return -1;
        int m = grid.size();
        int n = grid[0].size();
        int directions[5] = {0, 1, 0, -1, 0}; // Directions: right, down, left, up

        int dist[m][n];
        memset(dist,10001,sizeof(dist));
        dist[0][0] = 0;

        // Min-heap priority queue: {distance, {row, col}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        pq.push({0, {0, 0}}); // Start at (0, 0) with distance 0
        while (!pq.empty()) {
            auto [currentDist, cell] = pq.top();
            int x = cell.first;
            int y = cell.second;
            pq.pop();
            // Check if we reached the destination
            if (x == m - 1 && y == n - 1) return dist[x][y];
            int newdist = currentDist + 1;
            // Explore neighbors
            for (int i = 0; i < 4; ++i) {
                int nx = x + directions[i], ny = y + directions[i + 1];
                // Check if the new position is within boundaries and can be updated
                if (nx >= 0 && ny >= 0 && nx < m && ny < n && newdist < dist[nx][ny]) {
                    int tl = grid[nx][ny]; // Time limit for (nx, ny)
                    if (newdist >= tl) {
                        // Update distance if path is valid
                        dist[nx][ny] = newdist;
                        pq.push({newdist, {nx, ny}});
                    } else {
                        // Compute potential waiting time
                        if ((tl - currentDist) % 2) {
                            dist[nx][ny] = tl;
                            pq.push({tl, {nx, ny}});
                        } else {
                            dist[nx][ny] = tl + 1;
                            pq.push({tl + 1, {nx, ny}});
                        }
                    }
                }
            }
        }
        return -1; // If no path to the bottom-right corner exists
    }
};

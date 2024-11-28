class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> directions = {0, 1, 0, -1, 0}; // Directions: right, down, left, up
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq; // Min-heap
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX)); 
        dist[0][0] = 0;
        pq.push({0, {0, 0}}); 
        while (!pq.empty()) {
            auto [currentWeight, coords] = pq.top();
            auto [x, y] = coords;
            pq.pop();
            // If we've already found a better way to this cell, skip processing
            if (currentWeight > dist[x][y]) continue;
            // Check if we reached the destination
            if (x == m - 1 && y == n - 1) return currentWeight;
            for (int i = 0; i < 4; ++i) {
                int nx = x + directions[i], ny = y + directions[i + 1];
                if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                    int newWeight = currentWeight + grid[nx][ny]; // Add edge weight
                    // If this path is better, update distance and push to the heap
                    if (newWeight < dist[nx][ny]) {
                        dist[nx][ny] = newWeight;
                        pq.push({newWeight, {nx, ny}});
                    }
                }
            }
        }
        return -1; // If no path to the bottom-right corner exists
    }
};

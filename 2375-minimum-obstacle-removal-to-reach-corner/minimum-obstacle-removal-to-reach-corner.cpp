class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> directions = {0, 1, 0, -1, 0}; // Directions: right, down, left, up
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq; // Min-heap
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX)); // Distance matrix

        pq.emplace(0, 0, 0); // (current weight, x, y)
        dist[0][0] = 0;
        while (!pq.empty()) {
            auto [currentWeight, x, y] = pq.top();
            pq.pop();
            if (x == m - 1 && y == n - 1) return currentWeight;
            if (currentWeight > dist[x][y]) continue;
            for (int i = 0; i < 4; ++i) {
                int nx = x + directions[i], ny = y + directions[i + 1];

                if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                    int newWeight = currentWeight + grid[nx][ny]; // Add edge weight
                    // If this path is better, update distance and push to the heap
                    if (newWeight < dist[nx][ny]) {
                        dist[nx][ny] = newWeight;
                        pq.emplace(newWeight, nx, ny);
                    }
                }
            }
        }

        return -1; // If no path to the bottom-right corner exists
    }
};

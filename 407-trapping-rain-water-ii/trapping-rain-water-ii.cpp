#include <queue>
#include <vector>
#include <algorithm>

class Solution {
public:
    int trapRainWater(std::vector<std::vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        if (m <= 2 || n <= 2) return 0; // No water can be trapped if dimensions are too small
        
        // Priority queue to hold boundary cells, sorted by height (min-heap)
        std::priority_queue<std::tuple<int, int, int>, 
                            std::vector<std::tuple<int, int, int>>, 
                            std::greater<>> pq;
        
        // Visited array to track processed cells
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        // Add all boundary cells to the priority queue
        for (int i = 0; i < m; ++i) {
            pq.emplace(heightMap[i][0], i, 0);
            pq.emplace(heightMap[i][n - 1], i, n - 1);
            visited[i][0] = true;
            visited[i][n - 1] = true;
        }
        for (int j = 1; j < n-1; ++j) {
            pq.emplace(heightMap[0][j], 0, j);
            pq.emplace(heightMap[m - 1][j], m - 1, j);
            visited[0][j] = true;
            visited[m - 1][j] = true;
        }

        // Directions for exploring neighbors (up, down, left, right)
        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int ans = 0;

        // Process cells in priority queue
        while (!pq.empty()) {
            auto [height, x, y] = pq.top();
            pq.pop();

            // Visit all neighbors
            for (const auto& [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;

                // Check bounds and if the neighbor is already visited
                if (nx < 0 || ny < 0 || nx >= m || ny >= n || visited[nx][ny]) continue;

                // Calculate water trapped at the current neighbor
                ans += std::max(0, height - heightMap[nx][ny]);

                // Update height of neighbor to the max of its height or current cell height
                pq.emplace(std::max(height, heightMap[nx][ny]), nx, ny);
                visited[nx][ny] = true;
            }
        }

        return ans;
    }
};

/* #include <queue>
#include <vector>
#include <algorithm>

class Solution {
public:
    int trapRainWater(std::vector<std::vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        if (m <= 2 || n <= 2) return 0; // No water can be trapped if dimensions are too small
        
        // Priority queue to hold boundary cells, sorted by height (min-heap)
        std::priority_queue<std::tuple<int, int, int>, //height, x-coord,y-coord
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
}; */
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
    struct Cell {
        int x, y, h;
    };
    // min-heap on height
    struct Cmp {
        bool operator()(Cell const &a, Cell const &b) const {
            return a.h > b.h;
        }
    };
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.empty() || heightMap[0].empty()) return 0;
        int m = heightMap.size(), n = heightMap[0].size();
        // cannot trap water if less than 3×3
        if (m < 3 || n < 3) return 0;

        vector<vector<bool>> vis(m, vector<bool>(n,false));
        priority_queue<Cell, vector<Cell>, Cmp> pq;

        // 1) Push all border cells into the heap and mark them visited
        for (int i = 0; i < m; i++) {
            vis[i][0] = vis[i][n-1] = true;
            pq.push({i, 0, heightMap[i][0]});
            pq.push({i, n-1, heightMap[i][n-1]});
        }
        for (int j = 1; j < n-1; j++) {
            vis[0][j] = vis[m-1][j] = true;
            pq.push({0, j, heightMap[0][j]});
            pq.push({m-1, j, heightMap[m-1][j]});
        }

        int trapped = 0;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        // 2) Expand inward from lowest-height boundary inward
        while (!pq.empty()) {
            auto c = pq.top(); 
            pq.pop();
            for (auto &d : dirs) {
                int nx = c.x + d[0], ny = c.y + d[1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny]) 
                    continue;
                vis[nx][ny] = true;
                // if neighbor is lower, we trap water
                if (heightMap[nx][ny] < c.h) {
                    trapped += c.h - heightMap[nx][ny];
                }
                // push neighbor with the “water‐level” height
                pq.push({nx, ny, max(heightMap[nx][ny], c.h)});
            }
        }

        return trapped;
    }
};

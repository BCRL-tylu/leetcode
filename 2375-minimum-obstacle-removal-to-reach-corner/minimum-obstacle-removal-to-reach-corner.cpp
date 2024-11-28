#include <vector>
#include <deque>
#include <utility>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int directions[5] = {0, 1, 0, -1, 0}; // Directions: right, down, left, up
        int dist[m][n];
        memset(dist,-1,sizeof(dist));
        dist[0][0] = 0;
        deque<pair<int, int>> dq; // Deque for 0-1 BFS
        dq.emplace_front(0, 0); // Starting point
        while (!dq.empty()) {
            auto [x, y] = dq.front();
            dq.pop_front();
            // Check if we reached the destination
            if (x == m - 1 && y == n - 1) return dist[x][y];
            // Explore neighbors
            for (int i = 0; i < 4; ++i) {
                int nx = x + directions[i], ny = y + directions[i + 1];
                if (nx >= 0 && ny >= 0 && nx < m && ny < n && dist[nx][ny]==-1) {
                    // If this path is better, update distance
                        dist[nx][ny] = dist[x][y] + grid[nx][ny];
                        // Add to the front or back of the deque based on obstacle weight
                        if (grid[nx][ny]) {
                            dq.emplace_back(nx, ny); // No obstacle, higher priority
                        } else {
                            dq.emplace_front(nx, ny); // Obstacle, lower priority
                        }
                }
            }
        }
        return -1; // If no path to the bottom-right corner exists
    }
};

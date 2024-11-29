#include <climits>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if (grid[0][1] > 1 && grid[1][0] > 1)
            return -1;
        int m = grid.size(), n = grid[0].size();
        int dist[m * n];
        memset(dist, 10000, sizeof(dist));
        dist[0] = 0;
        // Priority queue: {distance, {row, col}}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, 0});
        // Directions: {right, down, left, up}
        int d[5] = {0, 1, 0, -1, 0};
        int waitTime;
        while (!pq.empty()) {
            auto [currentDist, cell] = pq.top();
            pq.pop();
            int x = cell % m, y = cell / m;
            // Early exit if we reached the destination
            if (x == m - 1 && y == n - 1)
                return currentDist;
            // Skip if already processed
            if (currentDist > dist[cell])
                continue;
            for (int i = 0; i < 4; ++i) {
                int nx = x + d[i], ny = y + d[i + 1];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;
                int c_pos = nx + ny * m;
                int newDist = currentDist + 1;
                int waitTime = grid[nx][ny] - newDist;
                if(waitTime > 0) newDist+= waitTime + waitTime % 2;
                // Adjust to next valid time if waitTime is odd
                if (newDist < dist[c_pos]) {
                    dist[c_pos] = newDist;
                    pq.push({dist[c_pos], c_pos});
                }
            }
        }
        return -1; // Return -1 if no valid path exists
    }
};

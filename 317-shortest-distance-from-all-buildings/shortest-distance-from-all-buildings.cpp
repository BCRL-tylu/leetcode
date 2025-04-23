class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> sumDist(m, vector<int>(n, 0));
        vector<vector<int>> reachCount(m, vector<int>(n, 0));
        vector<pair<int, int>> buildings;

        // Collect buildings' positions
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1)
                    buildings.emplace_back(i, j);
            }
        }
        int totalBuildings = buildings.size();
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // BFS from each building
        for (auto& [bi, bj] : buildings) {
            vector<vector<int>> dist(m, vector<int>(n, -1));
            queue<pair<int, int>> q;
            q.emplace(bi, bj);
            dist[bi][bj] = 0;

            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (auto& d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                        continue;
                    if (grid[nx][ny] != 0 || dist[nx][ny] != -1)
                        continue;
                    dist[nx][ny] = dist[x][y] + 1;
                    sumDist[nx][ny] += dist[nx][ny];
                    reachCount[nx][ny]++;
                    q.emplace(nx, ny);
                }
            }
        }

        int answer = INT_MAX;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 && reachCount[i][j] == totalBuildings) {
                    answer = min(answer, sumDist[i][j]);
                }
            }
        }

        return (answer == INT_MAX ? -1 : answer);
    }
};
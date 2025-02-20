int m, n, x, y, dp[500][500][5]{}, answer = 0, tx, ty, var, d;

class Solution {
public:
    int lenOfVDiagonal(std::vector<std::vector<int>>& grid) {
        m = grid.size(); n = grid[0].size(); answer = 0;

        for(x = 0; x < m; x++) for(y = 0; y < n; y++) --grid[x][y];
        
        // ↖ (x - 1, y - 1)
        x = 0; for(y = 0; y < n; y++) dp[x][y][1] = 1;
        y = 0; for(x = 0; x < m; x++) dp[x][y][1] = 1;
        for(x = 1; x < m; x++) {
            for(y = 1; y < n; y++) {
                if(grid[x][y] == +1) 
                    dp[x][y][1] = (grid[x - 1][y - 1] == -1)? 1 + dp[x - 1][y - 1][1]: 1;
                if(grid[x][y] == -1) 
                    dp[x][y][1] = (grid[x - 1][y - 1] == +1)? 1 + dp[x - 1][y - 1][1]: 1;
            }
        }

        // ↗ (x - 1, y + 1)
        x = 0; for(y = n - 1; y >= 0; y--) dp[x][y][2] = 1;
        y = n - 1; for(x = 0; x < m; x++) dp[x][y][2] = 1;
        for(x = 1; x < m; x++) {
            for(y = n - 2; y >= 0; y--) {
                if(grid[x][y] == +1) 
                    dp[x][y][2] = (grid[x - 1][y + 1] == -1)? 1 + dp[x - 1][y + 1][2]: 1;
                if(grid[x][y] == -1) 
                    dp[x][y][2] = (grid[x - 1][y + 1] == +1)? 1 + dp[x - 1][y + 1][2]: 1;
            }
        }
        
        // ↘ (x + 1, y + 1)
        x = m - 1; for(y = n - 1; y >= 0; y--) dp[x][y][3] = 1;
        y = n - 1; for(x = m - 1; x >= 0; x--) dp[x][y][3] = 1;
        for(x = m - 2; x >= 0; x--) {
            for(y = n - 2; y >= 0; y--) {
                if(grid[x][y] == +1) 
                    dp[x][y][3] = (grid[x + 1][y + 1] == -1)? 1 + dp[x + 1][y + 1][3]: 1;
                if(grid[x][y] == -1) 
                    dp[x][y][3] = (grid[x + 1][y + 1] == +1)? 1 + dp[x + 1][y + 1][3]: 1;
            }
        }

        // ↙ (x + 1, y - 1)
        x = m - 1; for(y = 0; y < n; y++) dp[x][y][4] = 1;
        y = 0; for(x = m - 1; x >= 0; x--) dp[x][y][4] = 1;
        for(x = m - 2; x >= 0; x--) {
            for(y = 1; y < n; y++) {
                if(grid[x][y] == +1) 
                    dp[x][y][4] = (grid[x + 1][y - 1] == -1)? 1 + dp[x + 1][y - 1][4]: 1;
                if(grid[x][y] == -1) 
                    dp[x][y][4] = (grid[x + 1][y - 1] == +1)? 1 + dp[x + 1][y - 1][4]: 1;
            }
        }

        for(x = 0; x < m; x++) {
            for(y = 0; y < n; y++) {
                if(std::abs(grid[x][y])) continue;

                answer = std::max(answer, 1);
                tx = x - 1, ty = y - 1, var = 1, d = 1;
                while(tx >= 0 && ty >= 0 && grid[tx][ty] == var) { 
                    answer = std::max(answer, d + dp[tx][ty][2]);
                    --tx; --ty; var = (var == 1)? -1: +1; ++d;
                }

                tx = x - 1, ty = y + 1, var = 1, d = 1;
                while(tx >= 0 && ty < n && grid[tx][ty] == var) { 
                    answer = std::max(answer, d + dp[tx][ty][3]);
                    --tx; ++ty; var = (var == 1)? -1: +1; ++d;
                }

                tx = x + 1, ty = y + 1, var = 1, d = 1;
                while(tx < m && ty < n && grid[tx][ty] == var) { 
                    answer = std::max(answer, d + dp[tx][ty][4]);
                    ++tx; ++ty; var = (var == 1)? -1: +1; ++d;
                }

                tx = x + 1, ty = y - 1, var = 1, d = 1;
                while(tx < m && ty >= 0 && grid[tx][ty] == var) { 
                    answer = std::max(answer, d + dp[tx][ty][1]);
                    ++tx; --ty; var = (var == 1)? -1: +1; ++d;
                }
            }
        }
        return answer;
    }
};
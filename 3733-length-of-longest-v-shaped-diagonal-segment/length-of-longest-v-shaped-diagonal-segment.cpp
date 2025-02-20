#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int>> dirs = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    int n, m;
    vector<vector<vector<vector<int>>>> memo; // Memoization table

    int dfs(int row, int col, int dir, bool turned, vector<vector<int>>& grid, int idx) {
        if (row < 0 || row >= n || col < 0 || col >= m) return 0;

        int prevRow = row - dirs[dir][0], prevCol = col - dirs[dir][1];

        if (idx == 1 && grid[row][col] == 0) return 0;
        if (idx > 0 &&
            (prevRow < 0 || prevRow >= n || prevCol < 0 || prevCol >= m ||
             grid[prevRow][prevCol] == grid[row][col] || grid[row][col] == 1)) {
            return 0;
        }

        if (memo[row][col][dir][turned] != -1) return memo[row][col][dir][turned];

        int sameDir = 1 + dfs(row + dirs[dir][0], col + dirs[dir][1], dir, turned, grid, idx + 1);

        int turnDir = 0;
        if (!turned) {
            int newDir = (dir + 1) % 4;
            turnDir = 1 + dfs(row + dirs[newDir][0], col + dirs[newDir][1], newDir, true, grid, idx + 1);
        }

        return memo[row][col][dir][turned] = max(sameDir, turnDir);
    }

    int lenOfVDiagonal(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        memo.assign(n, vector<vector<vector<int>>>(m, vector<vector<int>>(4, vector<int>(2, -1))));
        int maxLength = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    for (int d = 0; d < 4; d++) {
                        maxLength = max(maxLength, dfs(i, j, d, false, grid, 0));
                    }
                }
            }
        }
        return maxLength;
    }
};
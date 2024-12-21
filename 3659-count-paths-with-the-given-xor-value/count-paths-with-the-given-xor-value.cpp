#include <vector>
using namespace std;

class Solution {
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        const int MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        // Maximum XOR value
        const int MAX_XOR = 16;

        // 3D DP table: dp[x][y][xor_value] stores the number of ways to reach (x, y) with XOR == xor_value
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(MAX_XOR, 0)));

        // Initialize starting cell
        dp[0][0][grid[0][0]] = 1;

        // Fill DP table
        for (int x = 0; x < m; ++x) {
            for (int y = 0; y < n; ++y) {
                for (int current_xor = 0; current_xor < MAX_XOR; ++current_xor) {
                    if (dp[x][y][current_xor] == 0) continue; // Skip unreachable states

                    // Move Right
                    if (y + 1 < n) {
                        int new_xor = current_xor ^ grid[x][y + 1];
                        dp[x][y + 1][new_xor] = (dp[x][y + 1][new_xor] + dp[x][y][current_xor]) % MOD;
                    }

                    // Move Down
                    if (x + 1 < m) {
                        int new_xor = current_xor ^ grid[x + 1][y];
                        dp[x + 1][y][new_xor] = (dp[x + 1][y][new_xor] + dp[x][y][current_xor]) % MOD;
                    }
                }
            }
        }

        // Return paths ending at (m-1, n-1) with XOR == k
        return dp[m - 1][n - 1][k];
    }
};

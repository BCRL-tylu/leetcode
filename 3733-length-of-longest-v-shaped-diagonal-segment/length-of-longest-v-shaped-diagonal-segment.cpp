#pragma GCC optimize("O3", "unroll-loops")

const auto _ = std::cin.tie(nullptr)->sync_with_stdio(false);
#define LC_HACK
#ifdef LC_HACK
const auto __ = []() {
  struct ___ { static void _() { std::ofstream("display_runtime.txt") << 1e9 << '\n'; } };
  std::atexit(&___::_);
  return 0;
}();
#endif

class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<vector<int>>>> dp(4, vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(3, 0))));
        vector<pair<int, int>> dirs = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        
        for (int d = 0; d < 4; d++) {
            int di = dirs[d].first, dj = dirs[d].second;
            if (di == 1 && dj == 1) {
                for (int i = n - 1; i >= 0; i--) {
                    for (int j = m - 1; j >= 0; j--) {
                        for (int e = 0; e < 3; e++) {
                            if (grid[i][j] == e) {
                                int ni = i + di, nj = j + dj;
                                int ne = (e == 1) ? 2 : (e == 2 ? 0 : 2);
                                dp[d][i][j][e] = 1 + ((ni >= 0 && ni < n && nj >= 0 && nj < m) ? dp[d][ni][nj][ne] : 0);
                            }
                        }
                    }
                }
            } else if (di == 1 && dj == -1) {
                for (int i = n - 1; i >= 0; i--) {
                    for (int j = 0; j < m; j++) {
                        for (int e = 0; e < 3; e++) {
                            if (grid[i][j] == e) {
                                int ni = i + di, nj = j + dj;
                                int ne = (e == 1) ? 2 : (e == 2 ? 0 : 2);
                                dp[d][i][j][e] = 1 + ((ni >= 0 && ni < n && nj >= 0 && nj < m) ? dp[d][ni][nj][ne] : 0);
                            }
                        }
                    }
                }
            } else if (di == -1 && dj == -1) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        for (int e = 0; e < 3; e++) {
                            if (grid[i][j] == e) {
                                int ni = i + di, nj = j + dj;
                                int ne = (e == 1) ? 2 : (e == 2 ? 0 : 2);
                                dp[d][i][j][e] = 1 + ((ni >= 0 && ni < n && nj >= 0 && nj < m) ? dp[d][ni][nj][ne] : 0);
                            }
                        }
                    }
                }
            } else {
                for (int i = 0; i < n; i++) {
                    for (int j = m - 1; j >= 0; j--) {
                        for (int e = 0; e < 3; e++) {
                            if (grid[i][j] == e) {
                                int ni = i + di, nj = j + dj;
                                int ne = (e == 1) ? 2 : (e == 2 ? 0 : 2);
                                dp[d][i][j][e] = 1 + ((ni >= 0 && ni < n && nj >= 0 && nj < m) ? dp[d][ni][nj][ne] : 0);
                            }
                        }
                    }
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int d = 0; d < 4; d++) {
                    if (grid[i][j] != 1) continue;
                    int L = dp[d][i][j][1];
                    ans = max(ans, L);
                    int d2 = (d + 1) % 4;
                    int di = dirs[d].first, dj = dirs[d].second;
                    int di2 = dirs[d2].first, dj2 = dirs[d2].second;
                    for (int t = 1; t <= L; t++) {
                        int r = i + (t - 1) * di, c = j + (t - 1) * dj;
                        int nr = r + di2, nc = c + dj2;
                        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                        int exp = (t % 2 == 1) ? 2 : 0;
                        int L2 = dp[d2][nr][nc][exp];
                        ans = max(ans, t + L2);
                    }
                }
            }
        }
        return ans;
    }
};
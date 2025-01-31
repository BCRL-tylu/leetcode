#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_set>

class Solution {
public:
    int largestIsland(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        int groupSize[n * n + 1]; // Sizes of the islands
        std::memset(groupSize, 0, sizeof(groupSize));
        int groupId = 1; // Start group IDs from 1
        std::vector<std::vector<int>> color_mat(n, std::vector<int>(n, 0)); // Color matrix

        // DFS function as a lambda
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] != 1 || color_mat[i][j] != 0) {
                return 0; // Return 0 if out of bounds, not land, or already colored
            }
            color_mat[i][j] = groupId; // Mark the cell with the group ID
            return 1 + dfs(dfs, i + 1, j) + dfs(dfs, i - 1, j) + dfs(dfs, i, j + 1) + dfs(dfs, i, j - 1);
        };

        // Color the islands and calculate their sizes
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && color_mat[i][j] == 0) {
                    groupSize[groupId] = dfs(dfs, i, j);
                    groupId++;
                }
            }
        }

        int res = 0;
        // Check for each water cell the sizes of adjacent islands
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    int cur = 1; // Start with the current cell turning into land
                    std::unordered_set<int> adjacentGroups; // Store unique group IDs

                    // Check adjacent cells for their group IDs
                    if (i > 0) adjacentGroups.insert(color_mat[i - 1][j]);
                    if (i + 1 < n) adjacentGroups.insert(color_mat[i + 1][j]);
                    if (j > 0) adjacentGroups.insert(color_mat[i][j - 1]);
                    if (j + 1 < n) adjacentGroups.insert(color_mat[i][j + 1]);

                    // Add sizes of the adjacent groups
                    for (int group : adjacentGroups) {
                        if (group > 0) { // Only consider valid group IDs
                            cur += groupSize[group];
                        }
                    }
                    res = std::max(res, cur);
                }
            }
        }

        return res == 0 ? n * n : res; // Return the size of the largest island or n*n if no land exists
    }
};

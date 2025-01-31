class Solution {
private:
    int dfs(vector<vector<int>>& grid, vector<vector<int>>& colour_grid, int i, int j, int colourID) {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == 0 || colour_grid[i][j] != 0)
            return 0;

        colour_grid[i][j] = colourID; // Assign cluster ID
        int size = 1;

        // Explore 4 directions
        size += dfs(grid, colour_grid, i + 1, j, colourID);
        size += dfs(grid, colour_grid, i - 1, j, colourID);
        size += dfs(grid, colour_grid, i, j + 1, colourID);
        size += dfs(grid, colour_grid, i, j - 1, colourID);

        return size;
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<int>> colour_grid(rows, vector<int>(cols, 0));     // Store cluster IDs
        unordered_map<int, int> clusterSize; // Store size of each cluster

        int maxSize = 0;
        int colourID = 1; // Start coloring from 1

        // First pass: identify clusters and their sizes
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1 && colour_grid[i][j] == 0) {
                    int size = dfs(grid, colour_grid, i, j, colourID);
                    clusterSize[colourID] = size;
                    maxSize = max(maxSize, size);
                    colourID++;
                }
            }
        }

        int ans = maxSize; // Start with the largest island size found
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 0) {
                    unordered_set<int> uniqueClusters; // Use a set to track unique cluster IDs
                    int nums = 0;

                    // Check neighbors
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            if (abs(di) + abs(dj) == 1) { // Only consider orthogonal neighbors
                                int ni = i + di;
                                int nj = j + dj;
                                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                                    int neighbourClusterID = colour_grid[ni][nj];
                                    if (neighbourClusterID > 0 && uniqueClusters.insert(neighbourClusterID).second) {
                                        nums += clusterSize[neighbourClusterID];
                                    }
                                }
                            }
                        }
                    }

                    ans = max(ans, nums + 1); // Account for the current water cell
                }
            }
        }

        return ans;
    }
};

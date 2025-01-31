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
        int ans = INT_MIN;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 0) {
                        int nums = 0;
                        vector<int> clu_id;
                        if(i!=0){
                            nums+= clusterSize[colour_grid[i-1][j]];
                            clu_id.push_back(colour_grid[i-1][j]);
                        }
                        if(i != rows-1 && find(clu_id.begin(), clu_id.end(), colour_grid[i+1][j]) == clu_id.end()){
                            nums+= clusterSize[colour_grid[i+1][j]];
                            clu_id.push_back(colour_grid[i+1][j]);
                        }
                        if(j!=0 && find(clu_id.begin(), clu_id.end(), colour_grid[i][j-1]) == clu_id.end()){
                            nums+= clusterSize[colour_grid[i][j-1]];
                            clu_id.push_back(colour_grid[i][j-1]);
                        }
                        if(j != cols-1 && find(clu_id.begin(), clu_id.end(), colour_grid[i][j+1]) == clu_id.end()){
                            nums+= clusterSize[colour_grid[i][j+1]];
                            clu_id.push_back(colour_grid[i][j+1]);
                        }
                        ans = max(ans, nums+1);
                }
            }
        }
        if(ans == INT_MIN) return clusterSize[1];
        return ans;
    }
};

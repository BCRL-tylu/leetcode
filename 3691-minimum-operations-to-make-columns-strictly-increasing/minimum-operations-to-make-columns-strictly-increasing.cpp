#include <vector>
#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int totalOperations = 0;

        // Iterate through each column
        for (int j = 0; j < n; ++j) {
            for (int i = 1; i < m; ++i) {
                // Ensure that grid[i][j] > grid[i-1][j]
                if (grid[i][j] <= grid[i - 1][j]) {
                    int increment = grid[i - 1][j] + 1 - grid[i][j];
                    totalOperations += increment;
                    grid[i][j] += increment; // Update the grid to reflect the increment
                }
            }
        }
        return totalOperations;
    }
};

class Solution {
public:
    long long countSubmatrices(vector<vector<int>>& grid, int k) {
        int rows = grid.size();
        int cols = grid[0].size();

        int bar[rows][cols];
        for(int row = 0; row < rows; row++) {
            for(int col = cols - 1; col >= 0; col--) {
                if(grid[row][col] > k) {
                    bar[row][col] = 0;
                } else {
                    bar[row][col] = 1;
                    if(col < cols - 1 && grid[row][col + 1] <= grid[row][col]) {
                        bar[row][col] += bar[row][col + 1];
                    }
                }
            }
        }

        long long totalSum = 0;
        for(int col = 0; col < cols; col++) {
            
            vector<pair<int, int>> barStack = {{0, -1}}; // {bar, row}
            int sum = 0;

            for(int row = 0; row < rows; row++) {

                while(bar[row][col] < barStack.back().first) {

                    auto [barSize, barRow] = barStack.back();
                    barStack.pop_back();

                    int barDiff = barSize - max(barStack.back().first, bar[row][col]);
                    int boxHeight = row - barRow;
                    sum -= barDiff * boxHeight;

                    if(barStack.back().first < bar[row][col]) {
                        barStack.push_back({bar[row][col], barRow});
                    }
                }

                sum += bar[row][col];
                if(bar[row][col] > barStack.back().first) {
                    barStack.push_back({bar[row][col], row});
                }

                totalSum += sum;
            }
        }

        return totalSum;
    }
};
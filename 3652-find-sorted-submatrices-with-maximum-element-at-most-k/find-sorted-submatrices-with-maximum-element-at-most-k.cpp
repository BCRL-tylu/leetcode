#include <iostream>
#include <vector>
#include <stack>

class Solution {
public:
    long long countSubmatrices(std::vector<std::vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();

        // Step 1: Create dp array where dp[i][j] stores the number of valid submatrices
        // ending at (i, j) in its row.
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Skip cells greater than k
                if (grid[i][j] > k) continue;

                // Compute dp[i][j]: Count valid subarrays ending at (i, j) in the row
                dp[i][j] = (j > 0 && grid[i][j - 1] >= grid[i][j]) ? dp[i][j - 1] + 1 : 1;
            }
        }

        // Step 2: Transpose the dp array to process columns as rows
        std::vector<std::vector<int>> transposed(n, std::vector<int>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                transposed[j][i] = dp[i][j];
            }
        }

        // Step 3: Compute the total number of valid submatrices using numSubmat
        return numSubmat(transposed);
    }

private:
    long long numSubmat(const std::vector<std::vector<int>>& dp) {
        int m = dp.size(), n = dp[0].size();
        long long result = 0; // Use long long to avoid overflow

        // Process each row of the dp matrix
        for (int i = 0; i < m; ++i) {
            std::stack<int> st;  // Monotonic stack
            long long count = 0; // Use long long for accumulation

            for (int j = 0; j < n; ++j) {
                // Maintain a non-decreasing stack for the row
                while (!st.empty() && dp[i][st.top()] >= dp[i][j]) {
                    int r = st.top(); st.pop();       // Pop the top element
                    int l = st.empty() ? -1 : st.top(); // Determine the left boundary
                    count -= (long long)(dp[i][r] - dp[i][j]) * (r - l); // Adjust count
                }

                st.push(j);                // Push the current index
                count += dp[i][j];         // Add the current height
                result += count;           // Accumulate the total count
            }
        }

        return result;
    }
};

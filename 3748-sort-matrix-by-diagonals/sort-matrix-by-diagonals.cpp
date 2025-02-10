#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        vector<vector<int>> ans = grid;
        int n = grid.size();

        // Sorting diagonals above the main diagonal (ascending order)
        for (int i = 1; i < n; i++) {
            priority_queue<int, vector<int>, greater<int>> minHeap;
            for (int j = 0; j < n - i; j++) {
                minHeap.push(grid[j][j + i]); // Push elements into min-heap
            }
            for (int j = 0; j < n - i; j++) {
                ans[j][j + i] = minHeap.top(); // Extract sorted values
                minHeap.pop();
            }
        }

        // Sorting diagonals below the main diagonal (descending order)
        for (int i = 0; i < n; i++) {
            priority_queue<int> maxHeap;
            for (int j = 0; j < n - i; j++) {
                maxHeap.push(grid[i + j][j]); // Push elements into max-heap
            }
            for (int j = 0; j < n - i; j++) {
                ans[i + j][j] = maxHeap.top(); // Extract sorted values
                maxHeap.pop();
            }
        }

        return ans;
    }
};

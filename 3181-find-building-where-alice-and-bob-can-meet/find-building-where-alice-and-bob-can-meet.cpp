#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
private:
    std::vector<int> findNextGreater(const std::vector<int>& A) {
        int n = A.size();
        std::vector<int> B(n, -1); // Initialize B with -1
        std::stack<int> s;         // Stack to keep indices

        for (int i = n - 1; i >= 0; --i) {
            // Maintain the stack such that it only contains indices of elements
            // >= A[i]
            while (!s.empty() && A[s.top()] <= A[i]) {
                s.pop(); // Pop indices whose values are less than A[i]
            }
            // If the stack is not empty, the top element is the next greater or
            // equal
            if (!s.empty()) {
                B[i] = s.top();
            }
            // Push the current index onto the stack
            s.push(i);
        }

        return B;
    }
std::vector<int> computeMaxAfterIndexExcludingSelf(const std::vector<int>& arr) {
    int n = arr.size();
    std::vector<int> maxAfter(n, INT_MIN); // Initialize with the smallest possible value

    // Start from the second-to-last element, as the last element has no "after"
    for (int i = n - 2; i >= 0; --i) {
        maxAfter[i] = std::max(arr[i + 1], maxAfter[i + 1]);
    }

    return maxAfter;
}
public:
    std::vector<int>
    leftmostBuildingQueries(std::vector<int>& heights,
                            std::vector<std::vector<int>>& queries) {
        std::vector<int> G = findNextGreater(heights);
        std::vector<int> M = computeMaxAfterIndexExcludingSelf(heights);
        int size = queries.size();
        // Initialize a vector with all elements set to -1
        std::vector<int> ans(size, -1);
        
        for (int i = 0; i < size; i++) {
            std::vector<int> cq = queries[i];
            std::sort(cq.begin(), cq.end());
            int a = cq[0];
            int b = cq[1];
            if (a == b) {   // same building continue
                ans[i] = b; // Store in the correct position
                continue;
            }
            if (heights[b] > heights[a]) {
                ans[i] = b; // Store in the correct position
                continue;
            }
            if (heights[b] == heights[a]) {
                int next_greater_tob = G[b];
                ans[i] = next_greater_tob; // Store in the correct position
            }
            int threshold = heights[a];
            if(M[b]<threshold){
                ans[i] = -1;
                continue;
            }
            int next_greater_tob = max(G[b],G[a]);
            if (G[b] == -1 || G[a] == -1) {
                ans[i] = -1;
            } else {
                int greater_tob_value = heights[next_greater_tob];
                while (greater_tob_value <= threshold) {
                    next_greater_tob = G[next_greater_tob];
                    if (next_greater_tob == -1) {
                        ans[i] = -1;
                        break;
                    }
                    greater_tob_value = heights[next_greater_tob];
                }
                ans[i] = next_greater_tob;
            }
        }
        return ans;
    }
};

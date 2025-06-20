#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        stack<int> st;
        int water = 0;
        
        for (int i = 0; i < n; ++i) {
            // As long as the current bar is higher than the bar at stack top,
            // we can trap water over the bar at 'top'
            while (!st.empty() && height[i] > height[st.top()]) {
                int top = st.top();
                st.pop();
                if (st.empty()) break;  // no left boundary

                int left = st.top();
                int width = i - left - 1;
                int bounded_height = min(height[i], height[left]) - height[top];
                water += width * bounded_height;
            }
            st.push(i);
        }
        
        return water;
    }
};

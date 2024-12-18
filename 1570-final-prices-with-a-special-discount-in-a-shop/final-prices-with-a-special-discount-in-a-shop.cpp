class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        std::vector<int> ans = prices;
        std::stack<std::pair<int, int>> stack;
        int i = 0;
        while(i < n) {
            // Down the hill
            while (i + 1 < n && ans[i] >= ans[i + 1]) {
                ans[i] -= ans[i + 1];  // Correct subtraction
                i++;  // Move i after the subtraction
                while (!stack.empty()) {
                    auto current = stack.top();
                    if (ans[i] <= current.first) {
                        stack.pop();
                        ans[current.second] -= ans[i];
                    } else {
                        break;
                    }
                }
            }
            // Up the hill
            while (i + 1 < n && ans[i + 1] > ans[i]) {
                stack.push({ans[i], i});
                i++;
            }
            if(i == n-1){break;}
        }
        return ans;
    }
};

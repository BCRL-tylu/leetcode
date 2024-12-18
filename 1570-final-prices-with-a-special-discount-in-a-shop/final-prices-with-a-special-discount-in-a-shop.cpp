class Solution {
public:
    std::vector<int> finalPrices(std::vector<int>& prices) {
        int n = prices.size();
        std::vector<int> ans = prices;
        std::stack<std::pair<int, int>> stack;
        int i = 0;
        while(i < n-1) {
            while (i + 1 < n && ans[i] >= ans[i + 1]) {
                ans[i] -= ans[i + 1];
                i++;
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
            while (i + 1 < n && ans[i + 1] > ans[i]) {
                stack.push({ans[i], i++});
            }
        }
        return ans;
    }
};
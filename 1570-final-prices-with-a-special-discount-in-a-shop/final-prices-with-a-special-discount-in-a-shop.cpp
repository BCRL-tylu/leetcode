class Solution {
public:
    std::vector<int> finalPrices(std::vector<int>& prices) {
        int n = prices.size();
        std::vector<int> ans = prices;
        std::stack<int> stack;  // Store indices

        int i = 0;
        while (i < n-1) {
            // Down the hill: Apply discounts when prices[i] >= prices[i + 1]
            while (i + 1 < n && prices[i] >= prices[i + 1]) {
                ans[i] -= prices[i + 1];  // Apply discount to current price
                i++;  // Move to the next price after discount
                // Process any remaining items in the stack
                while (!stack.empty() && prices[stack.top()] >= prices[i]) {
                    ans[stack.top()] -= prices[i];  // Apply discount
                    stack.pop();  // Pop the index from the stack
                }
            }
            // Up the hill: Push indices to the stack when prices[i] < prices[i + 1]
            while (i + 1 < n && prices[i] < prices[i + 1]) {
                stack.push(i);  // Push current index onto the stack
                i++;
            }
        }

        return ans;
    }
};

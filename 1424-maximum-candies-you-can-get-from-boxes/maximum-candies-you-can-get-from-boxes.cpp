class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies,
                   vector<vector<int>>& keys,
                   vector<vector<int>>& containedBoxes,
                   vector<int>& initialBoxes) {
        int n = status.size(), ans = 0;
        vector<int> used(n, 0), hold(n, 0);

std::function<void(int)> dfs = [&](int start) -> void {
    if (used[start]) return;

    stack<int> stk;
    stk.push(start);

    while (!stk.empty()) {
        int c = stk.top();
        stk.pop();

        if (used[c]) continue;

        if (!status[c]) {
            hold[c] = true;
            continue;
        }

        ans += candies[c];
        used[c] = true;

        for (int k : keys[c]) {
            status[k] = true; 
            if (hold[k] && !used[k]) {
                dfs(k);
            }
        }

        // push any boxes contained within c
        for (int k : containedBoxes[c]) {
            if (!used[k]) {
                stk.push(k);
            }
        }
    }
};
 for (auto start : initialBoxes) {
            dfs(start);
        }
        return ans;
    }
};
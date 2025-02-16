class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> res(2 * n - 1, 0);
        vector<bool> used(n + 1, false);
        dfs(0, res, used, n);
        return res;
    }

    bool dfs(int idx, vector<int>& res, vector<bool>& used, int n) {
        if (idx == res.size()) return true; // Base case: all positions filled

        if (res[idx] != 0) return dfs(idx + 1, res, used, n); // Skip filled spots

        for (int num = n; num >= 1; --num) { // Try largest number first
            if (used[num]) continue;

            if (num == 1) { // 1 appears only once
                res[idx] = 1;
                used[num] = true;
                if (dfs(idx + 1, res, used, n)) return true;
                res[idx] = 0;
                used[num] = false;
            } else {
                int secondPos = idx + num;
                if (secondPos < res.size() && res[secondPos] == 0) {
                    res[idx] = res[secondPos] = num;
                    used[num] = true;
                    if (dfs(idx + 1, res, used, n)) return true;
                    res[idx] = res[secondPos] = 0;
                    used[num] = false;
                }
            }
        }
        return false;
    }
};

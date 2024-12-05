#include <iostream>
#include <vector>
#include <stack>

class Solution {
public:
long long countSubmatrices(vector<vector<int>>& g, int k) {
    long long m = g.size(), n = g[0].size(), res = 0;
    vector<vector<pair<int, int>>> mono(n);
    vector<int> mono_sum(n);
    for (int i = 0; i < m; ++i)
        for (int j = 0, len = 0; j < n; ++j)
            if (g[i][j] <= k) {
                len = (j && g[i][j - 1] >= g[i][j] ? len : 0) + 1;
                int len_count = 1;
                while (!mono[j].empty() && mono[j].back().first > len) {
                    len_count += mono[j].back().second;
                    mono_sum[j] -= mono[j].back().first * mono[j].back().second; 
                    mono[j].pop_back();
                }
                if (mono[j].empty() || mono[j].back().first != len)
                    mono[j].push_back({len, 0});
                mono[j].back().second += len_count;
                mono_sum[j] += len * len_count;
                res += mono_sum[j];
            }
            else {
                mono[j].clear();
                len = mono_sum[j] = 0;
            }
    return res;
}
};

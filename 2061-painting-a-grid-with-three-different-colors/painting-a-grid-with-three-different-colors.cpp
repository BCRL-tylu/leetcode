class Solution {
public:
    int colorTheGrid(int m, int n) {
        const int MOD = 1'000'000'007;

        // ——— replaced your cell-by-cell DP with a column-pattern DP ———

        // 1) build list of all 3^m column-patterns that have no two equal vertically
        vector<int> valid;
        int P = 1;
        for (int i = 0; i < m; ++i) P *= 3;
        for (int mask = 0; mask < P; ++mask) {
            int x = mask, prev = -1;
            bool ok = true;
            for (int i = 0; i < m; ++i) {
                int c = x % 3; x /= 3;
                if (c == prev) { ok = false; break; }
                prev = c;
            }
            if (ok) valid.push_back(mask);
        }
        int V = valid.size();

        // 2) precompute compatibility: two columns must differ in every row
        vector<vector<bool>> comp(V, vector<bool>(V,false));
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                int a = valid[i], b = valid[j];
                bool ok = true;
                for (int k = 0; k < m; ++k) {
                    if ((a % 3) == (b % 3)) { ok = false; break; }
                    a /= 3;  b /= 3;
                }
                comp[i][j] = ok;
            }
        }

        // 3) DP over columns: dp_prev[p] = #ways to paint up to previous column using pattern p
        vector<long long> dp_prev(V,1), dp_cur(V,0);
        // column 1: every valid pattern is 1 way
        for (int col = 2; col <= n; ++col) {
            fill(dp_cur.begin(), dp_cur.end(), 0);
            for (int i = 0; i < V; ++i) if (dp_prev[i]) {
                long long ways = dp_prev[i];
                for (int j = 0; j < V; ++j) if (comp[i][j]) {
                    dp_cur[j] = (dp_cur[j] + ways) % MOD;
                }
            }
            swap(dp_prev, dp_cur);
        }

        // 4) sum all ways for the last column
        long long ans = 0;
        for (auto &x : dp_prev) ans = (ans + x) % MOD;
        return int(ans);
    }
};

class Solution {
    void dfs(const vector<vector<int>> &con, int x, vector<bool> &mark, vector<int> &all) {
        if (mark[x]) return;
        mark[x] = true;
        for (int y : con[x]) {
            dfs(con, y, mark, all);
        } 
        all.push_back(x);
    }
    
    void dfs(const vector<vector<int>> &con, int x, vector<int> &id, int m) {
        if (id[x] >= 0) return;
        id[x] = m;
        for (int y : con[x]) {
            dfs(con, y, id, m);
        }
    }
public:
    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {
        vector<vector<int>> con(n), rcon(n);
        for (int i = 0; i < flowFrom.size(); ++i) {
            con[flowFrom[i]].push_back(flowTo[i]);
            rcon[flowTo[i]].push_back(flowFrom[i]);
        }
        vector<bool> mark(n);
        vector<int> all;
        for (int i = 0; i < n; ++i) {
            dfs(con, i, mark, all);
        }
        vector<int> id(n, -1);
        int m = 0;
        for (int i = n - 1; i >= 0; --i) {
            const int x = all[i];
            if (id[x] < 0) {
                dfs(rcon, x, id, m++);
            }
        }
        vector<bool> to(m);
        for (int i = 0; i < flowFrom.size(); ++i) {
            if (id[flowFrom[i]] != id[flowTo[i]]) {
                to[id[flowTo[i]]] = true;
            }
        }
        vector<bool> special(m);
        for (int x : crystals) {
            special[id[x]] = true;
        }
        int r = 0;
        for (int i = 0; i < m; ++i) {
            r += (!to[i] && !special[i]);
        }
        return r;
    }
};
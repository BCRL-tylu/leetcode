class HungarianAlgorithm {
private:
    vector<vector<int>> cost;
    vector<int> assignment;
    int optimalCost;

public:
    HungarianAlgorithm() {}

    int getRightMate(const int& row) { return assignment[row]; }

    int getAssignmentCost(const int& row) { return cost[row][assignment[row]]; }

    int getOptimalCost() { return optimalCost; }

    void addArcWithCost(const int& row, const int& col, const int& val) {
        if (row >= cost.size()) {
            cost.resize(row + 1,
                        vector<int>(cost.empty() ? 0 : cost[0].size(), 0));
        }
        if (col >= cost[0].size()) {
            for (auto& rowVec : cost) {
                rowVec.resize(col + 1, 0);
            }
        }
        cost[row][col] = val;
    }

    void solve() {
        int m = cost.size(), n = cost[0].size();
        vector<int> u(m + 1), v(n + 1), p(n + 1), way(n + 1);
        for (int i = 1; i <= m; ++i) {
            p[0] = i;
            int j0 = 0;
            vector<int> minv(n + 1, INT_MAX);
            vector<bool> used(n + 1, false);
            do {
                used[j0] = true;
                int i0 = p[j0], delta = INT_MAX, j1;
                for (int j = 1; j <= n; ++j)
                    if (!used[j]) {
                        int cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                        if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                        if (minv[j] < delta) delta = minv[j], j1 = j;
                    }
                for (int j = 0; j <= n; ++j)
                    if (used[j])
                        u[p[j]] += delta, v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        assignment.resize(n);
        for (int j = 1; j <= n; ++j) {
            assignment[p[j] - 1] = j - 1;
        }

        optimalCost = -v[0];
    }
};

class Solution {
private:
    HungarianAlgorithm* solver;

public:
    Solution() { solver = new HungarianAlgorithm(); }

    int findMinimumTime(vector<int>& strength) {
        for (int i = 0; i < strength.size(); ++i) {
            for (int j = 0; j < strength.size(); ++j) {
                int updateX = i + 1;
                solver->addArcWithCost(i, j, ceil(strength[j] * 1.0 / updateX));
            }
        }
        solver->solve();
        return solver->getOptimalCost();
    }
};
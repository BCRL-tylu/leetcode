class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        const int INF = 1e9;
        vector<int> ldo(n), rdo(n);
        int lastR = INF;
        for (int i = 0; i < n; ++i) {
            if (dominoes[i] == 'R') {
                lastR = i;
            } else if (dominoes[i] == 'L') {
                lastR = INF;
            }
            ldo[i] = lastR;
        }

        // 2) Right→Left sweep for 'L'
        int lastL = INF;
        for (int i = n - 1; i >= 0; --i) {
            if (dominoes[i] == 'L') {
                lastL = i;
            } else if (dominoes[i] == 'R') {
                lastL = INF;
            }
            rdo[i] = lastL;
        }

        // 3) Build answer
        string ans = dominoes;
        for (int i = 0; i < n; ++i) {
            if (dominoes[i] == '.') {
                int distR = (ldo[i] == INF ? INF : i - ldo[i]);
                int distL = (rdo[i] == INF  ? INF : rdo[i] - i);
                if (distR < distL)        ans[i] = 'R';
                else if (distL < distR)   ans[i] = 'L';
            }
        }

        return ans;
    }
};

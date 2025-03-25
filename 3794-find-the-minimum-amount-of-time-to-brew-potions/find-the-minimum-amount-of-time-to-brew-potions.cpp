class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size(), m = mana.size();
        vector<long long> prefix(n);
        prefix[0] = skill[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + skill[i];
        }
        
        vector<long long> finish(n, 0);
        
        finish[0] = (long long)skill[0] * mana[0];
        for (int i = 1; i < n; i++) {
            finish[i] = finish[i - 1] + (long long)skill[i] * mana[0];
        }
        
        for (int j = 1; j < m; j++) {
            long long S = 0;
            for (int i = 1; i < n; i++) {
                long long candidate = finish[i] - (long long) ( (i-1 >= 0 ? prefix[i - 1] : 0) ) * mana[j];
                S = max(S, candidate);
            }
            S = max(finish[0],S);
            vector<long long> newFinish(n, 0);
            newFinish[0] = S + (long long)skill[0] * mana[j];
            for (int i = 1; i < n; i++) {
                newFinish[i] = newFinish[i - 1] + (long long)skill[i] * mana[j];
            }
            finish = newFinish;
        }
        return finish[n - 1];
    }
};

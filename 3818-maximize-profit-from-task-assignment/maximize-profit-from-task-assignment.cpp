using pgq = priority_queue<int, vector<int>, greater<int>>;

class Solution {
public:
    long long maxProfit(vector<int>& workers, vector<vector<int>>& tasks) {
        unordered_map<int, int> cw;
        unordered_map<int, pgq> ts;
        for (int k : workers) {
            cw[k]++;
        }
        long long ans = 0;
        int ma = 0;
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (!cw.count(tasks[i][0])) {
                ma = max(ma, tasks[i][1]);
                continue;
            }
            if (ts[tasks[i][0]].size() < cw[tasks[i][0]]) {
                ts[tasks[i][0]].push(tasks[i][1]);
                ans += tasks[i][1];
            } else {
                int tor = ts[tasks[i][0]].top();
                if (tasks[i][1] < tor) {
                    ma = max(ma, tasks[i][1]);
                    continue;
                }else{
                    ts[tasks[i][0]].pop();
                    ts[tasks[i][0]].push(tasks[i][1]);
                    ans += tasks[i][1];
                    ans -= tor;
                    ma = max(ma, tor);
                }
            }
        }
        return ans+ma;
    }
};
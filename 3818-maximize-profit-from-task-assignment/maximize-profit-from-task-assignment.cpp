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

        for (const auto& task : tasks) {
            int skill = task[0], profit = task[1];

            auto it = cw.find(skill);
            if (it == cw.end()) {
                ma = max(ma, profit);
                continue;
            }

            auto& pq = ts[skill]; 

            if ((int)pq.size() < it->second) {
                pq.push(profit);
                ans += profit;
            } else if (profit > pq.top()) {
                ma = max(ma, pq.top()); 
                ans += profit - pq.top();
                pq.pop();
                pq.push(profit);
            } else {
                ma = max(ma, profit);
            }
        }
        return ans + ma;
    }
};
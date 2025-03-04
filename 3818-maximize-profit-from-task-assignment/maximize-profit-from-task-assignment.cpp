using pgq = priority_queue<int, vector<int>, greater<int>>;
struct Info { int cnt; pgq pq; };
class Solution {
public:
    long long maxProfit(vector<int>& worker, vector<vector<int>>& tasks) {
        unordered_map<int, Info> mp;
        mp.reserve(worker.size());
        for (int w : worker) {
            auto it = mp.find(w);
            if(it == mp.end())
                mp.emplace(w, Info{1, pgq()});
            else
                it->second.cnt++;
        }
        long long ans = 0;
        int ma = 0; // the additional worker's best profit
        for (auto &t : tasks) {
            int s = t[0], p = t[1];
            auto it = mp.find(s);
            if(it == mp.end()){
                ma = max(ma, p);
                continue;
            }
            auto &inf = it->second;
            if((int)inf.pq.size() < inf.cnt) {
                inf.pq.push(p);
                ans += p;
            } else if(p > inf.pq.top()){
                ma = max(ma, inf.pq.top());
                ans += p - inf.pq.top(); // remove less profitable job and add the most profitable
                inf.pq.pop();
                inf.pq.push(p);
            } else {
                ma = max(ma, p);
            }
        }
        return ans + ma;
    }
};

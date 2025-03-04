using pgq = priority_queue<int, vector<int>, greater<int>>;
struct Info { int cnt; pgq pq; };
class Solution {
public:
    long long maxProfit(vector<int>& W, vector<vector<int>>& T) {
        unordered_map<int, Info> mp;
        mp.reserve(W.size());
        for (int w : W) {
            auto it = mp.find(w);
            if(it == mp.end())
                mp.emplace(w, Info{1, pgq()});
            else
                it->second.cnt++;
        }
        long long ans = 0;
        int ma = 0;
        for (auto &t : T) {
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
                ans += p - inf.pq.top();
                inf.pq.pop();
                inf.pq.push(p);
            } else {
                ma = max(ma, p);
            }
        }
        return ans + ma;
    }
};

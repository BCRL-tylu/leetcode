using pgq = priority_queue<int, vector<int>, greater<int>>;
struct Info { int cnt; pgq pq; };
class Solution {
public:
long long maxProfit(vector<int>& workers, vector<vector<int>>& tasks) {
    long long res = 0, additionalWorker = 1;
    priority_queue<pair<int, int>> pq; // {profit, skill}
    for (const auto& t : tasks)
        pq.push( { t[1], t[0] } );
    unordered_map<int, int> wrks; // {skill, cnt}
    for (const int& w : workers)
        wrks[w]++;
    while (!pq.empty()) {
        auto [profit, skill] = pq.top();
        pq.pop();
        if (wrks[skill] > 0 || additionalWorker > 0) {
            res += profit;
            if (wrks[skill] > 0)
                wrks[skill]--;
            else
                additionalWorker = 0;
        }
    }
    return res;
}
};

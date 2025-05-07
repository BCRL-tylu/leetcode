using ll =long long;
using T3 = tuple<int,int,int>;

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size(), m = moveTime[0].size();
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        priority_queue<T3, vector<T3>, greater<T3>> pq;
        
        dist[0][0] = 0;
        pq.emplace(0, 0, 0);
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        while (!pq.empty()) {
            auto [t, i, j] = pq.top(); pq.pop();
            if (t > dist[i][j]) continue;
            if (i == n-1 && j == m-1)
                return t;
            
            for (auto& d : dirs) {
                int x = i + d[0], y = j + d[1];
                if (x<0 || x>=n || y<0 || y>=m) continue;
                ll nt = max<ll>(t, moveTime[x][y]) + 1;
                if (nt < dist[x][y]) {
                    dist[x][y] = nt;
                    pq.emplace(nt, x, y);
                }
            }
        }
        return -1;
    }
};
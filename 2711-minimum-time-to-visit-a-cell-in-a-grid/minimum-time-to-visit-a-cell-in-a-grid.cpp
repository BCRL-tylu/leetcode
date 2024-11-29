class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if (grid[0][1] > 1 && grid[1][0] > 1) return -1;
        short m = grid.size(), n = grid[0].size();
        int dist[m*n];
        memset(dist,9000, sizeof(dist));
        dist[0] = 0;
        // Priority queue: {distance, {row, col}}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, 0});
        // Directions: {right, down, left, up}
        short d[5] = {0, 1, 0, -1, 0};
        int waitTime,i;
        while (!pq.empty()) {
            auto [currentDist, cell] = pq.top();
            pq.pop();
            short x = cell % m, y = cell/m;
            // Early exit if we reached the destination
            if (x == m - 1 && y == n - 1)
                return currentDist;
            // Skip if already processed
            if (dist[cell]<currentDist) continue;
            i = 0;
            while(i < 4) {
                int nx = x + d[i], ny = y + d[++i];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;
                int c_pos = nx + ny * m;
                int md = currentDist+1;
                waitTime = grid[nx][ny] - md;
                if(waitTime > 0){
                    md+= waitTime + waitTime % 2;
                }
                // Adjust to next valid time if waitTime is odd
                if (md < dist[c_pos]) {
                    dist[c_pos] = md;
                    pq.push({md, c_pos});
                }
            }
        }
        return -1; // Return -1 if no valid path exists
    }
};

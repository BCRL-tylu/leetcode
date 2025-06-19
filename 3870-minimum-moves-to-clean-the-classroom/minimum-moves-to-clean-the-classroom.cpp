class Solution {
public:
    struct State {
        int x, y;
        int e;
        int mask;
        int steps;
    };
    
    int minMoves(vector<string>& room, int maxEnergy) {
        int n = room.size();
        int m = room[0].size();
        
        // 1) find S and all the L’s
        int sx = -1, sy = -1;
        vector<pair<int,int>> lits;
        vector<vector<int>> litIdx(n, vector<int>(m, -1));
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(room[i][j] == 'S'){
                    sx = i; sy = j;
                } else if(room[i][j] == 'L'){
                    litIdx[i][j] = lits.size();
                    lits.emplace_back(i, j);
                }
            }
        }
        
        int L = lits.size();
        int allMask = (1<<L) - 1;
        
        // 2) bestEnergy[x][y][mask] = max energy we've ever arrived with
        vector<vector<vector<int>>> bestEnergy(n,
            vector<vector<int>>(m,
                vector<int>(1<<L, -1)
            )
        );
        
        // 3) BFS queue
        deque<State> q;
        q.push_back({sx, sy, maxEnergy, 0, 0});
        bestEnergy[sx][sy][0] = maxEnergy;
        
        const int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        
        while(!q.empty()){
            auto cur = q.front(); 
            q.pop_front();
            
            // if we’ve collected all litter, we’re done
            if(cur.mask == allMask) 
                return cur.steps;
            
            int e = cur.e;
            // reset on R
            if(room[cur.x][cur.y] == 'R') 
                e = maxEnergy;
            
            // try 4 neighbors
            for(auto &d: dirs){
                int nx = cur.x + d[0];
                int ny = cur.y + d[1];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m) 
                    continue;
                if(room[nx][ny] == 'X') 
                    continue;
                if(e == 0) 
                    continue;  // no energy to move
                
                int ne = e - 1;
                int nmask = cur.mask;
                if(room[nx][ny] == 'L'){
                    int id = litIdx[nx][ny];
                    nmask |= (1<<id);
                }
                
                // have we ever arrived here with ≥ this energy & same mask?
                if(bestEnergy[nx][ny][nmask] >= ne) 
                    continue;
                
                bestEnergy[nx][ny][nmask] = ne;
                q.push_back({nx, ny, ne, nmask, cur.steps + 1});
            }
        }
        
        return -1;
    }
};

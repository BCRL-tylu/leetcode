class Solution {
    vector<int> visited;

private:
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        visited.assign(n, 0);
        stack<int> q;
        vector<vector<int>> adj(n);
        int ans =0;
        for (auto u : edges) {
            adj[u[0]].push_back(u[1]);
            adj[u[1]].push_back(u[0]);
        }
        for (int i = 0; i < n; i++) {
            if (visited[i] & 1) continue;
            q.push(i);
            visited[i] = 1;
            int ncount = 1,ecount=0;
            while (!q.empty()) {
                int node = q.top();
                q.pop();
                for (auto kid : adj[node]) {
                    ecount++;
                    if (visited[kid] & 1) continue;
                    q.push(kid);
                    ncount++;
                    visited[kid] =1;
                }
            }
            if(ecount ==ncount*(ncount-1)) ans++;
        }
        return ans;
    }
};
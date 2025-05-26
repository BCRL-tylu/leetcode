class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size(), m = edges.size();
        vector<array<int,26>> freq(n);
        vector<int> indeg(n, 0);
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            indeg[e[1]]++;
        }
        for (int u = 0; u < n; u++) {
            freq[u][colors[u]-'a'] = 1;
        }

        stack<int> q;
        for (int u = 0; u < n; u++) if (indeg[u] == 0) q.push(u);
        

        int seen = 0, ans = 0;
        while (!q.empty()) {
            int u = q.top(); q.pop();
            seen++;
            for (int c = 0; c < 26; c++) 
                ans = max(ans, freq[u][c]);
            
            for (int v : adj[u]) {
                for (int c = 0; c < 26; c++) {
                    int add = (colors[v]-'a' == c);
                    freq[v][c] = max(freq[v][c], freq[u][c] + add);
                }
                if (--indeg[v] == 0) q.push(v);
            }
        }
        return (seen < n ? -1 : ans);
    }
};

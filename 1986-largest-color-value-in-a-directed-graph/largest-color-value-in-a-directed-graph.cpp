class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size(), m = edges.size();
        vector<vector<int>> adj(n);
        vector<int> indegree(n, 0);

        // build graph + indegrees
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            indegree[v]++;
        }

        // freq[i][c] = max count of letter 'a'+c on any path ending at i
        vector<array<int,26>> freq(n);
        // initialize freq[u][its own color] = 1
        for (int u = 0; u < n; u++) {
            freq[u][colors[u] - 'a'] = 1;
        }

        // Kahn’s queue of zero‐indegree nodes
        queue<int> q;
        for (int u = 0; u < n; u++) {
            if (indegree[u] == 0)
                q.push(u);
        }

        int seen = 0, ans = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            seen++;
            // update global answer from freq[u]
            for (int c = 0; c < 26; c++)
                ans = max(ans, freq[u][c]);

            // “relax” edges u→v
            for (int v : adj[u]) {
                // transfer dp from u to v
                for (int c = 0; c < 26; c++) {
                    // if path to u has freq[u][c], then to v it's either that
                    // or plus one if v’s color==c
                    int add = (colors[v]-'a' == c);
                    freq[v][c] = max(freq[v][c], freq[u][c] + add);
                }
                // decrease indegree and maybe enqueue
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }

        // if we never saw all nodes, there was a cycle
        if (seen < n)
            return -1;
        return ans;
    }
};

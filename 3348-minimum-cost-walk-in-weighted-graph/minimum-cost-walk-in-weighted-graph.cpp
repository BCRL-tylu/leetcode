class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        // Initialize DSU arrays.
        vector<int> parent(n), compAND(n, ~0); // ~0 gives all bits 1.
        vector<int> size(n, 1);
        iota(parent.begin(), parent.end(), 0);
        
        // DSU find with path compression.
        function<int(int)> find = [&](int x) -> int {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };
        
        // DSU union that also updates the global AND for the component.
        auto unionn = [&](int a, int b, int w) {
            a = find(a); 
            b = find(b);
            if(a == b) {
                // If they're already in the same component, update the component AND.
                compAND[a] &= w;
                return;
            }
            // Merge the smaller component into the larger one.
            if(size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            // The new component's global AND is the AND of the two previous components' ANDs and the new edge.
            compAND[a] &= compAND[b] & w;
        };
        
        // Process each edge.
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            unionn(u, v, w);
        }
        
        // Answer the queries.
        vector<int> ans;
        for (auto &q : query) {
            int u = q[0], v = q[1];
            if (find(u) != find(v))
                ans.push_back(-1);
            else
                ans.push_back(compAND[find(u)]);
        }
        return ans;
    }
};

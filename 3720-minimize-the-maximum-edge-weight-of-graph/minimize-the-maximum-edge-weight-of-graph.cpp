class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (auto &it : edges)
            graph[it[1]].emplace_back(it[0], it[2]);

        vector<bool> visited(n);          // Tracks visited nodes
        vector<int> key(n, INT_MAX);      // Minimum weights to each node
        key[0] = 0;                       // Start with node 0
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, 0);                 // {weight, node}

        // Process nodes
        for (int i = 0; i < n; i++) {
            while (!pq.empty() && visited[pq.top().second])
                pq.pop();

            if (pq.empty()) return -1;    // If no valid path, return -1

            auto it = pq.top();
            pq.pop();
            int idx = it.second;

            visited[idx] = true;

            // Update neighbors
            for (auto &nbr : graph[idx]) {// nbr = {node, weight}
                if (!visited[nbr.first] && key[nbr.first] > nbr.second) { // if the neighbour not visited and minimum weight assigfned(default maximum) bigger than edge weighted
                    key[nbr.first] = nbr.second;
                    pq.emplace(nbr.second, nbr.first);
                }
            }
        }

        // Return the maximum edge weight in the solution
        return *max_element(key.begin(), key.end());
    }
};
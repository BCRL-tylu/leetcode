class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<int> dist1(n, -1), dist2(n, -1);
        
        // helper to fill dist[*] from start
        auto walk = [&](int start, vector<int>& dist){
            int d = 0, cur = start;
            while (cur != -1 && dist[cur] == -1) {
                dist[cur] = d++;
                cur = edges[cur];
            }
        };
        
        walk(node1, dist1);
        walk(node2, dist2);
        
        int ans = -1, best = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (dist1[i] >= 0 && dist2[i] >= 0) {
                int cost = max(dist1[i], dist2[i]);
                if (cost < best) {
                    best = cost;
                    ans  = i;
                }
            }
        }
        return ans;
    }
};

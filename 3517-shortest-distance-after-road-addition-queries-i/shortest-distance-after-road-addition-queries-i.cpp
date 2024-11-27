class Solution {
    public:vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<pair<int, int>> hm(n); // [parent, distance]
        vector<vector<int>> children(n); // Store children for each node
        hm[0] = {n, 0}; // Root node
        for (int i = 1; i < n; i++) {
            hm[i] = {i - 1, i}; // Parent and initial distance
            children[i - 1].push_back(i); // Add child relationship
        }
        vector<int> rt(queries.size());
        for (int j = 0; j < queries.size(); j++) {
            int newParent = queries[j][0];
            int node = queries[j][1];
            children[newParent].push_back(node);
            int nps = hm[newParent].second + 1;
            if (hm[node].second>nps) {
                hm[node]= {newParent,nps};
                queue<int> q;
                q.push(node); // add the tail of query edge to queue list
                while (!q.empty()) {
                    int curr = q.front(); // get the first element of queue
                    q.pop(); //remove it
                    int updated = hm[curr].second + 1;
                    for (int child : children[curr]) {
                    if(hm[child].second>updated){
                        hm[child].second = updated;
                        q.push(child);
                        }
                    }
                }
            }
            rt[j] = hm[n - 1].second;
        }
        return rt;
    }
};
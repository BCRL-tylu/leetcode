class Solution {
public:

    int countComponents(vector<int>& nums, int threshold) {
        int n = nums.size();
        unordered_map<int, vector<int>> adj;

        int components = 0;
        
        for(int j = 0; j < n; j ++) {
            int num = nums[j];
            if(num > threshold) components ++;
            for(int i = 1 * num; i <= threshold; i += num) {
        
                adj[num].push_back(i);
                adj[i].push_back(num);
            }
        }

        unordered_map<int, int> vis;
        
        
        for(auto it: adj) {
            int i = it.first;
            queue<int> q;
            if(vis[i] == 1) continue;
            q.push(i);
            vis[i] = 1;
            components ++;
            while(! q.empty()) {
                auto u = q.front();
                q.pop();
                for(auto v: adj[u]) {
                    if(!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return components;
    }
};
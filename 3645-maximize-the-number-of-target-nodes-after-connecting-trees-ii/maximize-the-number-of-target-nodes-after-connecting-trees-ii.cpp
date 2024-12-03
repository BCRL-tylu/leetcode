class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
    int mk = 0;
    unordered_map<int, vector<int>> adj1;
    unordered_map<int, vector<int>> adj2;

    for (auto& edge : edges1) {
        adj1[edge[0]].push_back(edge[1]);
        adj1[edge[1]].push_back(edge[0]);
        mk = max(mk,max(edge[0],edge[1]));
    }
    for (auto& edge : edges2) {
        adj2[edge[0]].push_back(edge[1]);
        adj2[edge[1]].push_back(edge[0]);
    }
    // Step 2: BFS to label nodes and count labels
    unordered_map<int, int> labels; // Store labels of nodes
    unordered_map<int, int> hm = {{0, 0}, {1, 0}}; // Count of labels

    queue<int> q; // Queue for BFS
    // Start BFS from the root node (arbitrarily choose 0)
    int root = edges1[0][0];
    labels[root] = 0; // Start with label 0
    hm[0]++; // Increment label 0 count
    q.push(root);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int neighbor : adj1[current]) {
            if (labels.find(neighbor) == labels.end()) { // If unvisited
                labels[neighbor] = 1 - labels[current]; // Alternate label
                hm[labels[neighbor]]++; // Increment count for this label
                q.push(neighbor);
            }
        }
    }

    unordered_map<int, bool> visited2; 
    queue<pair<int, int>> q2; // Queue for BFS
    // Start BFS from the root node (arbitrarily choose 0)
    int count0 = 0, count1 = 0; // Counters for labels 0 and 1
    int root2 = edges2[0][0];
    q2.push({root2, 0});
    visited2[root2] = true;
    count0++;
    while (!q2.empty()) {
        auto [current, label] = q2.front();
        q2.pop();
        for (int neighbor : adj2[current]) {
            if (!visited2[neighbor]) { // If unvisited
                int newLabel = 1 - label; // Alternate label
                if (newLabel == 0) count0++;
                else count1++;
                visited2[neighbor] = true;
                q2.push({neighbor, newLabel});
            }
        }
    }
    int sec = max(count0, count1);
    // Step 3: Return the maximum count of labels
    vector<int> rt;

    for(int i=0; i<=mk;i++){
        rt.push_back(hm[labels[i]]+sec);
    }
    return rt;  
    }
};

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        // Build graph and in-degree array
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        for (auto& prereq : prerequisites) {
            adj[prereq[0]].push_back(prereq[1]);
            inDegree[prereq[1]]++;
        }

        // Topological Sort and Matrix Propagation with Bitwise Optimization
        vector<bitset<200>> isPrerequisite(numCourses); // Replace matrix with bitset (faster updates)
        queue<int> q;
        // Add all nodes with in-degree 0 to the queue
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (int next : adj[current]) {
                isPrerequisite[next] |= isPrerequisite[current];
                isPrerequisite[next][current] = true;
                if (--inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        // Answer Queries
        vector<bool> ans;
        for (auto& query : queries) {
            ans.push_back(isPrerequisite[query[1]][query[0]]);
        }
        return ans;
    }
};

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        // Step 1: Build graph and in-degree array
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        for (auto& prereq : prerequisites) {
            adj[prereq[0]].push_back(prereq[1]);
            inDegree[prereq[1]]++;
        }

        // Step 2: Topological Sort and Matrix Propagation with Bitwise Optimization
        vector<bitset<500>> isPrerequisite(numCourses); // Replace matrix with bitset (faster updates)
        queue<int> q;

        // Add all nodes with in-degree 0 to the queue
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int course = q.front();
            q.pop();

            for (int next : adj[course]) {
                // Use bitwise OR to merge prerequisite information
                isPrerequisite[next] |= isPrerequisite[course];
                isPrerequisite[next][course] = true; // Add the current course itself as a prerequisite

                if (--inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        // Step 3: Answer Queries
        vector<bool> ans;
        for (auto& query : queries) {
            ans.push_back(isPrerequisite[query[1]][query[0]]);
        }

        return ans;
    }
};

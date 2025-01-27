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

        // Step 2: Topological Sort and Track Prerequisites in a Matrix
        vector<vector<bool>> isPrerequisite(numCourses, vector<bool>(numCourses, false));
        queue<int> q;

        // Add all nodes with in-degree 0 to the queue
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int course = q.front();
            q.pop();
            for (int next : adj[course]) {
                // Update the matrix for all prerequisites of the current course
                for (int i = 0; i < numCourses; ++i) {
                    if (isPrerequisite[i][course]) {
                        isPrerequisite[i][next] = true;
                    }
                }
                // Mark the current course as a prerequisite for the child
                isPrerequisite[course][next] = true;

                // Decrement in-degree and add to queue if it becomes 0
                if (--inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        // Step 3: Answer Queries
        vector<bool> ans;
        for (auto& query : queries) {
            ans.push_back(isPrerequisite[query[0]][query[1]]);
        }

        return ans;
    }
};

#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    vector<vector<int>> supersequences(const vector<string>& words) {
        // 1. Determine the set U of letters and mark forced ones.
        set<char> used;
        vector<bool> forced(26, false);
        for (const auto &w : words) {
            for (char ch : w)
                used.insert(ch);
            if (w[0] == w[1])
                forced[w[0]-'a'] = true;
        }
        
        // Build a sorted vector of used letters.
        vector<char> letters(used.begin(), used.end());
        int n = letters.size();
        // Map letter -> index (0 to n-1)
        unordered_map<char,int> letterToIndex;
        for (int i = 0; i < n; i++){
            letterToIndex[letters[i]] = i;
        }
        
        // 2. Precompute the edge matrix.
        // edge[i][j] is true if there is a word "xy" (with x != y) such that letter i = x and letter j = y.
        vector<vector<bool>> edge(n, vector<bool>(n, false));
        for (const auto &w : words) {
            if (w[0] == w[1]) continue;
            int u = letterToIndex[w[0]];
            int v = letterToIndex[w[1]];
            edge[u][v] = true;
        }
        
        // 3. Determine which letters are "free" (not forced).
        vector<int> freeIndices;
        for (int i = 0; i < n; i++) {
            if (!forced[letters[i]-'a'])
                freeIndices.push_back(i);
        }
        int freeCount = freeIndices.size();
        
        // We'll iterate over all assignments for free letters.
        // For each letter in freeIndices:
        //   bit = 0 means frequency 1; bit = 1 means frequency 2.
        vector<vector<int>> validAssignments;  // store assignment arrays (size n) for valid assignments.
        int minTotal = INT_MAX;
        
        // There are 2^(freeCount) possibilities.
        for (int mask = 0; mask < (1 << freeCount); mask++) {
            // Build the assignment array for all letters in U.
            // For forced letters, frequency is 2.
            // For free letters, frequency is determined by the bit in mask.
            vector<int> assignment(n, 0);
            int total = 0;
            // Set free letters.
            for (int j = 0; j < freeCount; j++) {
                int idx = freeIndices[j];
                // If the bit is set, assign frequency 2; otherwise 1.
                if (mask & (1 << j)) {
                    assignment[idx] = 2;
                    total += 2;
                } else {
                    assignment[idx] = 1;
                    total += 1;
                }
            }
            // Set forced letters.
            for (int i = 0; i < n; i++) {
                if (forced[letters[i]-'a'])
                {
                    assignment[i] = 2;
                    total += 0; // They are already set to 2.
                }
            }
            // Prune if total is not minimal.
            if (total > minTotal) continue;
            
            // 4. Check ordering constraints for letters with frequency 1.
            // Build the set of vertices (indices) with frequency 1.
            vector<int> freeVertices;
            for (int i = 0; i < n; i++) {
                if (assignment[i] == 1)
                    freeVertices.push_back(i);
            }
            
            // Use Kahn's algorithm to check acyclicity of the subgraph induced on freeVertices.
            int r = freeVertices.size();
            vector<int> indegree(n, 0);
            // Compute indegree only for vertices in freeVertices.
            for (int u : freeVertices) {
                for (int v : freeVertices) {
                    if (edge[u][v])
                        indegree[v]++;
                }
            }
            // Kahn's algorithm: remove vertices with zero indegree.
            queue<int> q;
            for (int u : freeVertices) {
                if (indegree[u] == 0)
                    q.push(u);
            }
            int removed = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                removed++;
                for (int v : freeVertices) {
                    if (edge[u][v]) {
                        indegree[v]--;
                        if (indegree[v] == 0)
                            q.push(v);
                    }
                }
            }
            if (removed != r) continue;  // cycle exists, skip assignment.
            
            // Valid assignment.
            if (total < minTotal) {
                minTotal = total;
                validAssignments.clear();
            }
            if (total == minTotal)
                validAssignments.push_back(assignment);
        }
        
        // 5. Build the final result: each valid assignment becomes a 26-element frequency array.
        vector<vector<int>> result;
        for (auto &assign : validAssignments) {
            vector<int> freq(26, 0);
            // Only letters in U get a nonzero frequency.
            for (int i = 0; i < n; i++) {
                char ch = letters[i];
                freq[ch - 'a'] = assign[i];
            }
            result.push_back(freq);
        }
        return result;
    }
};

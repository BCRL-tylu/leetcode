#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    // DFS to compute the hash and count of characters for each node
    pair<long long, int> dfs(vector<long long> &has, int mod, vector<vector<int>> &g, int curr, string &s, vector<long long> &pow) {
        int count = 0;
        long long hash = 0;

        // Traverse children of the current node
        for (int child : g[curr]) {
            pair<long long, int> p = dfs(has, mod, g, child, s, pow);
            if (count == 0) {
                hash = p.first; // First child hash
            } else {
                hash = (hash + (p.first * pow[count]) % mod) % mod; // Combine hashes
            }
            count += p.second; // Increment count of characters
        }

        // Add current node's character
        hash = (hash + (pow[count] * (s[curr] - 'a')) % mod) % mod;
        has[curr] = hash; // Store hash for current node
        count++; // Increment count for the current node
        return {hash, count};
    }

    // Reverse DFS to compute the hash from the end
    pair<long long, int> redfs(vector<long long> &rehas, int mod, vector<vector<int>> &g, int curr, string &s, vector<long long> &pow) {
        int count = 1; // Start with one for the current character
        long long hash = s[curr] - 'a'; // Hash for the current character
        
        // Process children in reverse order
        for (int i = g[curr].size() - 1; i >= 0; i--) {
            int child = g[curr][i];
            pair<long long, int> p = redfs(rehas, mod, g, child, s, pow);
            hash = (hash + (p.first * pow[count]) % mod) % mod; // Combine hashes
            count += p.second; // Increment count
        }
        rehas[curr] = hash; // Store reverse hash for current node
        return {hash, count};
    }

    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<long long> hash(n, -1), rehash(n, -1);
        vector<vector<int>> g(n);

        // Build the tree from parent array
        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                g[parent[i]].push_back(i);
            }
        }

        // Sort children to ensure order
        for (int i = 0; i < n; i++) {
            sort(g[i].begin(), g[i].end());
        }

        // Precompute powers of base 31
        vector<long long> pow(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            pow[i] = (pow[i - 1] * 31) % 1000000009;
        }

        vector<bool> ans(n, true); // Initialize results to true
        dfs(hash, 1000000009, g, 0, s, pow); // Compute normal hashes
        redfs(rehash, 1000000009, g, 0, s, pow); // Compute reverse hashes
        
        // Check if hashes match for palindrome property
        for (int i = 0; i < n; i++) {
            ans[i] = rehash[i] == hash[i];
        }
        return ans; // Return the result
    }
};

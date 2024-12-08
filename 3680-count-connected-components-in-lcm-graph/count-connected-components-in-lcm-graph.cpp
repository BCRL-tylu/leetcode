


class Solution {
    int uf[101010]; // Union-Find parent array to keep track of connected components

    // Find function with path compression
    int find(int u) {
        // If the current node is not its own parent, recursively find its root and compress the path
        return uf[u] == u ? u : uf[u] = find(uf[u]);
    }

    // Union function to merge two components
    void uni(int u, int v) {
        int pu = find(u), pv = find(v); // Find roots of both nodes
        uf[pu] = uf[pv] = min(pu, pv); // Link both roots to the smaller root
    }

public:
    int countComponents(vector<int>& nums, int threshold) {
        int res = 0; // Result to store the number of connected components
        
        // Initialize Union-Find: Each node starts as its own parent
        for (int i = 0; i < nums.size(); i++) uf[i] = i;

        // `cover` array to track the first index of a number divisible by a given multiple
        vector<int> cover(threshold + 1, -1);

        // Process each number in `nums`
        for (int i = 0; i < nums.size(); i++) {
            // Iterate over multiples of `nums[i]` up to the threshold
            for (int j = nums[i]; j <= threshold; j += nums[i]) {
                if (cover[j] == -1) {
                    // If no node is associated with this multiple, mark the current node as the representative
                    cover[j] = i;
                } else {
                    // If another node is already associated with this multiple, union the current node with it
                    uni(cover[j], i);
                                    // Optimization: If `j` is exactly `nums[i]`, break the loop
                // (no need to process other multiples for the current number)
                if (j == nums[i]) break;
                }
            }
        }

        // Count unique components by checking how many nodes are their own root
        for (int i = 0; i < nums.size(); i++) {
            if (find(i) == i) res++; // If `i` is its own root, it's a distinct component
        }

        return res; // Return the number of connected components
    }
};

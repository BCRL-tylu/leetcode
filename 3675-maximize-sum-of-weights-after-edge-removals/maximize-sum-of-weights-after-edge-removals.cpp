typedef long long LL; // Shorthand for long long to simplify writing large integer types
typedef pair<int, int> pii; // Shorthand for a pair of integers (e.g., edges with node IDs)
typedef pair<LL, int> pli; // Shorthand for a pair of a long long (e.g., weight sum) and an integer (delta)
typedef vector<int> vi; // Shorthand for a vector of integers

vector<pii> e[100000]; // Adjacency list for the graph, storing edges as pairs (neighbor, weight)

int st[100001]; // Stack to hold edge benefits during computation
int sp; // Stack pointer to manage the "active" part of the stack

greater<int> gi; // Comparator for sorting in descending order (used by nth_element)

class Solution {
public:
    /**
     * Recursive function to compute the maximum weight of the subtree rooted at node `x`.
     * It ensures that no node has more than `k` edges.
     * @param x: Current node
     * @param par: Parent node (to avoid revisiting the parent edge)
     * @param k: Maximum number of edges allowed for each node
     * @return pli: A pair containing:
     *              - First: Maximum weight of the subtree
     *              - Second: Delta for choosing the k-th edge in the parent scenario
     */
    pli f(int x, int par, int k) {
        LL ret = 0; // To store the maximum weight of the subtree rooted at `x`
        const int N = e[x].size(); // Number of neighbors of node `x`
        int sp0 = sp; // Save the current stack pointer (to isolate this node's computations)
        int *buf = st + sp; // Pointer to the start of this node's buffer in the stack

        // Process all neighbors of `x`
        for (auto &p : e[x]) {
            if (par == p.first) continue; // Skip the parent node to avoid backtracking
            auto p2 = f(p.first, x, k); // Recursively compute the child's subtree weight and delta
            ret += p2.first; // Add the child's subtree weight to the total weight
            int tmp = p.second - p2.second; // Compute the "benefit" of including this edge
            if (tmp > 0) st[sp++] = tmp; // If the benefit is positive, store it in the stack
        }

        int n = sp - sp0; // Number of benefits collected for this node
        if (n >= k) {
            // If more than `k` benefits, find the top `k` using nth_element
            nth_element(buf, buf + k - 1, buf + n, gi);
        }

        int mi = min(n, k); // Choose the smaller of `n` and `k` (to avoid accessing out-of-bounds memory)
        for (int i = 0; i < mi; i++) {
            ret += buf[i]; // Add the top `mi` benefits to the total weight
        }

        sp = sp0; // Reset the stack pointer to its previous state

        // Return the maximum weight and the k-th benefit (or 0 if there are fewer than `k`)
        if (k <= n) return pli(ret, buf[k - 1]);
        else return pli(ret, 0);
    }

    /**
     * Main function to compute the maximum sum of weights in a tree while respecting the degree constraint.
     * @param edges: List of edges in the format {node1, node2, weight}
     * @param k: Maximum number of edges allowed for each node
     * @return Maximum possible sum of weights
     */
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        // Build the adjacency list from the input edges
        for (auto &t : edges) {
            int x = t[0];
            int y = t[1];
            int z = t[2];
            e[x].push_back(pii(y, z));
            e[y].push_back(pii(x, z));
        }

        // Start the recursion from the root node (0), with no parent (-1)
        LL ret = f(0, -1, k).first;

        // Clear the adjacency list for reuse
        int n = edges.size() + 1; // Number of nodes in the graph
        for (int i = 0; i < n; i++) e[i].clear();

        return ret; // Return the maximum weight
    }
};

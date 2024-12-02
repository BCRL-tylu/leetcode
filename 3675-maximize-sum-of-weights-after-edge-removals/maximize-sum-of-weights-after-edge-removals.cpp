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
        // e type vector<pair<int, int>> - e[node] = pair{adj_node,weight}
        int sp0 = sp; // Save the current stack pointer (to isolate this node's computations)
        //The expression st + sp uses pointer arithmetic. Here, st is a pointer to the first element of the array st.
        //The result of st + sp is of type int* (a pointer to an integer). It points to the location in memory corresponding to the element at index sp of the st array.
        int *buf = st + sp; // Pointer to the start of this node's buffer in the stack

        // Process all neighbors of `x`
        for (auto &p : e[x]) {
            if (par == p.first) continue; // Skip the parent node to avoid backtracking
            auto p2 = f(p.first, x, k); // Recursively compute the child's subtree weight and delta
            ret += p2.first; // Add the child's subtree weight to the total weight
            int tmp = p.second - p2.second; // p.second = weight of edge xp, Compute the "benefit" of including this edge
            // for nodes adjacent to end vertices/or a node with degree more than k, p2.second = 0
            // for other nodes, p2.second = buf[k - 1], the code is accessing the element at the k-th position (0-indexed) in the array that buf points st+sp, which is the smallest contribution the last node can make,

            // tmp bascially compard the weight of edge x(current node)p(adjacent node by iteration) and the weight of smallest contribution that p can make, we can keep that edge, as the edge has been counted, so we better keep it.
            if (tmp > 0) st[sp++] = tmp; // If the benefit is positive, store it in the stack
        }
        // st[sp++] the increments make from p.second - p2.second
        int n = sp - sp0; // Number of benefits collected for this node
        if (n >= k) {
            // If more than `k` benefits, find the top `k` using nth_element
            //   int *buf = st + sp; // Pointer to the start of this node's buffer in the stack
            nth_element(buf, buf + k - 1, buf + n, gi);
            // find top k element in memory location from buf to buf+k-1, total k numbers, buf+n represents the end of the range
        }

        int mi = min(n, k); // Choose the smaller of `n` and `k` (to avoid accessing out-of-bounds memory)
        // we need the degree of the node
        for (int i = 0; i < mi; i++) {
            ret += buf[i]; // Add the top `mi` benefits to the total weight
        }

        sp = sp0; // Reset the stack pointer to its previous state

        // Return the maximum weight and the k-th benefit (or 0 if there are fewer than `k`)
        // pair<LL, int> pli
        if (k <= n) return pli(ret, buf[k - 1]);
        // for end vertices which doesn't initliate any edges
        else return pli(ret, 0);
    }

    /**
     * Main function to compute the maximum sum of weights in a tree while respecting the degree constraint.
     * @param edges: List of edges in the format {node1, node2, weight}
     * @param k: Maximum number of edges allowed for each node
     * @return Maximum possible sum of weights
     */
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        // Build the adjacency list from the input edges e[node] = pair{adj_node,weight}
        for (auto &t : edges) {
            int x = t[0];
            int y = t[1];
            int z = t[2];
            e[x].push_back(pii(y, z));
            e[y].push_back(pii(x, z));
        }

        // Start the recursion from the root node (0), with no parent (-1)
        LL ret = f(0, -1, k).first;//f(Current node, Parent node,Maximum number of edges allowed for each node)

        // Clear the adjacency list for reuse
        int n = edges.size() + 1; // Number of nodes in the graph
        for (int i = 0; i < n; i++) e[i].clear();

        return ret; // Return the maximum weight
    }
};

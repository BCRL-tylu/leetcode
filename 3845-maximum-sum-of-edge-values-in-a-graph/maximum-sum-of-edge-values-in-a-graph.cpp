class Solution {
public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        // build adjacency
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // find connected components
        vector<char> seen(n, 0);
        vector<vector<int>> comp_nodes;
        vector<bool> comp_isCycle;
        vector<int> comp_edges;
        for (int i = 0; i < n; i++) {
            if (seen[i]) continue;
            // DFS
            stack<int> st;
            st.push(i);
            seen[i] = 1;
            vector<int> nodes;
            int edge_sum = 0;
            while (!st.empty()) {
                int u = st.top(); st.pop();
                nodes.push_back(u);
                edge_sum += adj[u].size();
                for (int v : adj[u]) {
                    if (!seen[v]) {
                        seen[v] = 1;
                        st.push(v);
                    }
                }
            }
            int m_i = edge_sum / 2;
            comp_nodes.push_back(nodes);
            comp_edges.push_back(m_i);
            // cycle if #edges == #nodes
            comp_isCycle.push_back(m_i == (int)nodes.size());
        }

        int C = comp_nodes.size();
        // build index list and sort by (edges desc, isCycle desc)
        vector<int> order(C);
        iota(order.begin(), order.end(), 0);
// new comparison (by comp_edges/comp_nodes.size(), ties broken arbitrarily)
sort(order.begin(), order.end(), [&](int a, int b){
    // compare comp_edges[a]/size[a]  vs comp_edges[b]/size[b]
    long lhs = (long)comp_edges[a] * comp_nodes[b].size();
    long rhs = (long)comp_edges[b] * comp_nodes[a].size();
    if (lhs != rhs) 
        return lhs > rhs;
    // (only happens when edges_a/nodes_a == edges_b/nodes_b)
    // break ties by (say) larger component first
    if (comp_nodes[a].size() != comp_nodes[b].size())
        return comp_nodes[a].size() > comp_nodes[b].size();
    return a < b;
});


        // labels to assign
        long long cur_label = n;
        vector<long long> val(n, 0);

        // for each component in sorted order
        for (int ix : order) {
            auto& nodes = comp_nodes[ix];
            int c = nodes.size();
            // take the top c labels: [cur_label-c+1 ... cur_label]
            vector<long long> S(c);
            for (int j = 0; j < c; j++) {
                S[j] = cur_label - c + 1 + j;
            }
            vector<long long> P;
            P.reserve(c);

            if (comp_isCycle[ix]) {
                // cycle: odd-indices (1-based even) ascending, then even-indices descending
                // 0-based odd positions:
                for (int j = 1; j < c; j += 2) 
                    P.push_back(S[j]);
                int start = ((c-1) % 2 == 0 ? c-1 : c-2);
                for (int j = start; j >= 0; j -= 2) 
                    P.push_back(S[j]);
            } else {
                // path: even-positions ascending, then odd-positions descending
                for (int j = 0; j < c; j += 2) 
                    P.push_back(S[j]);
                int start = (((c-1) % 2) == 1 ? c-1 : c-2);
                for (int j = start; j >= 1; j -= 2) 
                    P.push_back(S[j]);
            }

            // get the traversal order of this component
            vector<int> tour;
            tour.reserve(c);
            if (comp_isCycle[ix]) {
                // pick arbitrary start and walk the cycle
                int u0 = nodes[0], prev = -1, u = u0;
                do {
                    tour.push_back(u);
                    int nxt = (adj[u][0] == prev ? adj[u][1] : adj[u][0]);
                    prev = u;
                    u = nxt;
                } while (u != u0);
            } else {
                // find an endpoint (degree<=1) to start the path
                int start_node = nodes[0];
                for (int u : nodes) {
                    if ((int)adj[u].size() <= 1) {
                        start_node = u;
                        break;
                    }
                }
                int u = start_node, prev = -1;
                while (true) {
                    tour.push_back(u);
                    int nxt = -1;
                    for (int v : adj[u]) {
                        if (v != prev) {
                            nxt = v;
                            break;
                        }
                    }
                    if (nxt < 0) break;
                    prev = u;
                    u = nxt;
                }
            }

            // assign labels along the tour
            for (int j = 0; j < c; j++) {
                val[tour[j]] = P[j];
            }
            cur_label -= c;
        }

        // compute total score
        long long ans = 0;
        for (auto& e : edges) {
            ans += val[e[0]] * val[e[1]];
        }
        return ans;
    }
};

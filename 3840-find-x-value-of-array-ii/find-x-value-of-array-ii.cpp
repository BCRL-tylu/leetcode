#include <bits/stdc++.h>
using namespace std;
class Solution {
    int n, k;
    struct Node { int prod; int freq[5][5]; };
    vector<Node> st;
    vector<int> A;
    Node merge(const Node &L, const Node &R) {
        Node P;
        P.prod = (L.prod * R.prod) % k;
        for (int s = 0; s < k; s++) {
            int mid = (s * L.prod) % k;
            for (int t = 0; t < k; t++) {
                P.freq[s][t] = L.freq[s][t] + R.freq[mid][t];
            }
        }
        return P;
    }
    void init_leaf(int p, int i) {
        Node &nd = st[p];
        nd.prod = A[i];
        for (int s = 0; s < k; s++)
            for (int t = 0; t < k; t++)
                nd.freq[s][t] = 0;
        for (int s = 0; s < k; s++)
            nd.freq[s][(s * A[i]) % k] = 1;
    }
    void build(int p, int l, int r) {
        if (l == r) { init_leaf(p, l); return; }
        int m = (l + r) >> 1;
        build(p<<1, l, m);
        build(p<<1|1, m+1, r);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }
    void update(int p, int l, int r, int idx) {
        if (l == r) { init_leaf(p, l); return; }
        int m = (l + r) >> 1;
        if (idx <= m) update(p<<1, l, m, idx);
        else          update(p<<1|1, m+1, r, idx);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }
    Node query(int p, int l, int r, int i, int j) {
        if (i <= l && r <= j) return st[p];
        int m = (l + r) >> 1;
        if (j <= m)      return query(p<<1,     l,   m, i, j);
        if (i >  m)      return query(p<<1|1, m+1,   r, i, j);
        return merge(query(p<<1, l, m, i, j),
                     query(p<<1|1, m+1, r, i, j));
    }
public:
    vector<int> resultArray(vector<int>& nums, int k_, vector<vector<int>>& queries) {
        n = nums.size();
        k = k_;
        if (k == 1) {
            vector<int> ans;
            ans.reserve(queries.size());
            for (auto &q : queries)
                ans.push_back(n - q[2]);
            return ans;
        }
        A.resize(n);
        for (int i = 0; i < n; i++)
            A[i] = ((nums[i] % k) + k) % k;
        st.resize(4*n);
        build(1, 0, n-1);
        vector<int> ans;
        ans.reserve(queries.size());
        for (auto &q : queries) {
            int idx = q[0];
            int v = ((q[1] % k) + k) % k;
            int start = q[2];
            int x = q[3];
            if (A[idx] != v) {
                A[idx] = v;
                update(1, 0, n-1, idx);
            }
            Node nd = query(1, 0, n-1, start, n-1);
            ans.push_back(nd.freq[1][x]);
        }
        return ans;
    }
};

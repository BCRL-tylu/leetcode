#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// 1) Fenwick supporting range‐add / point‐query in O(log N)
struct RangeFenwick {
    int N;
    vector<int> f;
    RangeFenwick(int n): N(n), f(n+1,0) {}
    // build from A[0..n-1]
    RangeFenwick(const vector<int>& A): N((int)A.size()), f(N+1,0) {
        // build difference D
        vector<int> D(N+1);
        D[1] = A[0];
        for(int i=2;i<=N;i++) D[i] = A[i-1] - A[i-2];
        // linear‐time BIT build on D
        for(int i=1;i<=N;i++){
            f[i] += D[i];
            int j = i + (i & -i);
            if(j<=N) f[j] += f[i];
        }
    }
    // add v at index i in the internal tree
    void bit_update(int i,int v){
        for(; i<=N; i += i&-i)
            f[i] += v;
    }
    // prefix‐sum query
    int bit_query(int i) const {
        int s=0;
        for(; i>0; i -= i&-i)
            s += f[i];
        return s;
    }
    // public: add v to A[l..r]
    void range_add(int l,int r,int v){
        if(l>r) return;
        // our Fenwick is 1-indexed internally
        bit_update(l+1,     v);
        bit_update(r+2,    -v);
    }
    // public: read A[x]
    int point_query(int x) const {
        // internally we stored D at 1..N, so query at x+1
        return bit_query(x+1);
    }
};

class Solution {
public:
    int maxRemoval(vector<int>& nums,
                   vector<vector<int>>& queries) {
        int n = nums.size(), m = queries.size();
        // 2) Fenwick over initial nums
        RangeFenwick rf(nums);

        // 3) prepare all queries with (l, r, id)
        struct Q{int l,r,id;};
        vector<Q> qs;
        qs.reserve(m);
        for(int i=0;i<m;i++)
            qs.push_back({queries[i][0],
                          queries[i][1], i});
        // sort by left ascending
        sort(qs.begin(), qs.end(),
             [](auto &a, auto &b){
                return a.l < b.l;
             });

        // 4) sweep i=0..n-1, maintain max-heap by r
        priority_queue<pair<int,int>> pq; 
        vector<bool> used(m,false);
        int ptr = 0, usedCount = 0;

        for(int i=0; i<n; i++){
            // push all intervals starting at ≤ i
            while(ptr < m && qs[ptr].l <= i) {
                pq.push({ qs[ptr].r, ptr });
                ptr++;
            }
            // while nums[i]>0, consume intervals
            while(rf.point_query(i) > 0) {
                // drop already-used
                while(!pq.empty() && used[ qs[pq.top().second].id ])
                    pq.pop();
                if(pq.empty())
                    return -1;       // no more intervals to cover i

                // pick the one with largest r
                auto [r, idx] = pq.top(); 
                pq.pop();

                auto &q = qs[idx];
                used[q.id] = true;
                usedCount++;

                // apply its effect: decrement A[q.l..q.r] by 1
                rf.range_add(q.l, q.r, -1);
            }
        }

        return m - usedCount;
    }
};

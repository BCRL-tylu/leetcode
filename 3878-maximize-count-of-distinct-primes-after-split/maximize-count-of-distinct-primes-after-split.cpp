#include <bits/stdc++.h>
using namespace std;

/*
 We maintain:
  - nums[0..n-1], n >= 2.
  - A segment‐tree over the array V[0..n-2], where
       V[t] = (sum_{j=0}^t cntL[j]) - (sum_{j=0}^t cntR[j]) .
    The segment‐tree supports range‐add and range‐max in O(log n).
  - cntL[i] = # of distinct primes p whose FIRST occurrence is exactly i.
  - cntR[i] = # of distinct primes p whose LAST  occurrence is exactly i.
    (So cntL, cntR are arrays of length n.)
  - D = # of distinct primes currently appearing in nums.

  For each prime value p, we keep a set<int> S[p] = { all indices i where nums[i] == p }.
  Then L_p = *S[p].begin(), R_p = *S[p].rbegin(), if S[p] non‐empty.

  After we change nums[idx] = newVal in a query:
   1) Let oldVal = nums[idx].  If oldVal was prime, remove idx from S[oldVal],
      adjust cntL and cntR and D accordingly (with up to 4 segment‐tree updates).
   2) Set nums[idx] = newVal.  If newVal is prime, insert idx into S[newVal],
      adjust cntL and cntR and D accordingly (with up to 4 segment‐tree updates).
   3) Answer = D + (current segment‐tree maximum over V[0..n-2]).

  Precompute isPrime[1..100000] by a sieve in O(10^5 log log 10^5).
*/

static const int MAXVAL = 100000;

struct SegTree {
    // We store a 0-based array of length M = n-1 (n>=2).  We will build on indices [0..M-1].
    // Each leaf holds V[t] for t in [0..M-1].  We support range_add(l,r,delta) and getMax().

    int n;                // actually storing M = (original n) - 1
    vector<long long> st; // segment‐tree max
    vector<long long> lz; // lazy tags (to add to a whole segment)

    SegTree(int _n): n(_n) {
        st.assign(4*n, 0LL);
        lz.assign(4*n, 0LL);
    }

    // build from a length‐n array arr[0..n-1].
    void build(int node, int L, int R, const vector<long long> &arr) {
        if (L == R) {
            st[node] = arr[L];
        } else {
            int mid = (L + R) >> 1;
            build(node<<1, L, mid, arr);
            build(node<<1|1, mid+1, R, arr);
            st[node] = max(st[node<<1], st[node<<1|1]);
        }
    }

    // push‐down lazy tag
    void push_down(int node, int L, int R) {
        if (lz[node] != 0) {
            st[node] += lz[node];
            if (L < R) {
                lz[node<<1]   += lz[node];
                lz[node<<1|1] += lz[node];
            }
            lz[node] = 0;
        }
    }

    // range‐add Δ on [i..j]
    void update_range(int node, int L, int R, int i, int j, long long delta) {
        push_down(node, L, R);
        if (j < L || R < i) return;
        if (i <= L && R <= j) {
            lz[node] += delta;
            push_down(node, L, R);
            return;
        }
        int mid = (L + R) >> 1;
        update_range(node<<1,   L,    mid, i, j, delta);
        update_range(node<<1|1, mid+1, R,  i, j, delta);
        st[node] = max(st[node<<1], st[node<<1|1]);
    }

    // query the max over [0..n-1]
    long long getMax() {
        push_down(1, 0, n-1);
        return st[1];
    }
};


class Solution {
public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        int n = (int)nums.size();
        int M = n - 1;            // number of valid split‐positions t = 0..n-2

        // 1) Sieve up to 100000
        static bool isPrime[MAXVAL+1];
        for(int i = 0; i <= MAXVAL; i++) isPrime[i] = false;
        {
            vector<bool> sieve(MAXVAL+1, true);
            sieve[0] = false;
            sieve[1] = false;
            for(int i = 2; i*i <= MAXVAL; i++) {
                if(sieve[i]) {
                    for(int j = i*i; j <= MAXVAL; j += i) {
                        sieve[j] = false;
                    }
                }
            }
            for(int i = 2; i <= MAXVAL; i++) {
                isPrime[i] = sieve[i];
            }
        }

        // 2) For each prime value p in [2..100000], keep a set<int> of all indices i where nums[i] == p
        static set<int> positions[MAXVAL+1];
        for(int v = 0; v <= MAXVAL; v++) {
            positions[v].clear();
        }

        // 3) cntL[i], cntR[i], initially zero
        vector<int> cntL(n, 0), cntR(n, 0);
        int D = 0; // how many distinct primes currently appear at least once

        // Insert initial array‐contents into the sets
        for(int i = 0; i < n; i++) {
            int v = nums[i];
            if(v <= MAXVAL && isPrime[v]) {
                positions[v].insert(i);
            }
        }
        // Now initialize cntL, cntR, and D
        for(int p = 2; p <= MAXVAL; p++) {
            if(isPrime[p] && !positions[p].empty()) {
                D++;
                int Lp = *positions[p].begin();
                int Rp = *positions[p].rbegin();
                cntL[Lp] += 1;
                cntR[Rp] += 1;
            }
        }

        // 4) Build initial array V[0..M-1], where
        //    prefixL[i] = sum_{j=0..i} cntL[j], prefixR[i] = sum_{j=0..i} cntR[j].
        //    V[i] = prefixL[i] - prefixR[i].
        vector<long long> V(M, 0LL);
        if (M > 0) {
            long long sumL = 0, sumR = 0;
            for(int i = 0; i < M; i++) {
                sumL += cntL[i];
                sumR += cntR[i];
                V[i] = sumL - sumR;
            }
        }

        // 5) Build a segment‐tree of size M = n-1 on array V[0..M-1].
        SegTree seg(M);
        if (M > 0) {
            seg.build(1, 0, M-1, V);
        }

        auto range_add = [&](int pos, long long delta) {
            // We want to add `delta` to V[t] for all t in [pos..M-1], PROVIDED pos <= M-1
            if (pos < 0) pos = 0;
            if (pos > M-1) return;
            seg.update_range(1, 0, M-1, pos, M-1, delta);
        };

        // 6) Now process each query
        int Q = (int)queries.size();
        vector<int> answer(Q, 0);

        for(int qi = 0; qi < Q; qi++) {
            int idx = queries[qi][0];
            int val = queries[qi][1];
            int oldVal = nums[idx];

            // === (A) Remove old occurrence, if oldVal was prime ===
            if(oldVal <= MAXVAL && isPrime[oldVal]) {
                auto &S = positions[oldVal];
                // We'll remove idx from S.  First record old L,R:
                int oldL = *S.begin();
                int oldR = *S.rbegin();

                // Erase idx
                S.erase(idx);

                if(S.empty()) {
                    // That prime vanishes altogether:
                    D--;
                    // We must do cntL[oldL]--  => V[t]-- for all t>= oldL
                    cntL[oldL]--;
                    range_add(oldL, -1);
                    // We must do cntR[oldR]--  => V[t]++ for all t>= oldR  (because subtracting from sumR)
                    cntR[oldR]--;
                    range_add(oldR, +1);
                } else {
                    // Still at least one occurrence remains.  Let newL,newR be the new extremes
                    int newL = *S.begin();
                    int newR = *S.rbegin();
                    if(newL != oldL) {
                        // The “first occurrence” moved from oldL to newL:
                        //   cntL[oldL]--  => V[t]-- for t>=oldL
                        cntL[oldL]--;
                        range_add(oldL, -1);
                        //   cntL[newL]++  => V[t]++ for t>=newL
                        cntL[newL]++;
                        range_add(newL, +1);
                    }
                    if(newR != oldR) {
                        // The “last occurrence” moved from oldR to newR:
                        //   cntR[oldR]-- => V[t]++ for t>=oldR   (since sumR[t] drops by 1)
                        cntR[oldR]--;
                        range_add(oldR, +1);
                        //   cntR[newR]++ => V[t]-- for t>=newR   (since sumR[t] rises by 1)
                        cntR[newR]++;
                        range_add(newR, -1);
                    }
                }
            }

            // === (B) Insert new occurrence, if val is prime ===
            nums[idx] = val;  
            if(val <= MAXVAL && isPrime[val]) {
                auto &S = positions[val];
                if(S.empty()) {
                    // Prime did not exist before; now it appears exactly at idx
                    D++;
                    S.insert(idx);
                    // cntL[idx]++, cntR[idx]++
                    cntL[idx]++;
                    range_add(idx, +1);
                    cntR[idx]++;
                    range_add(idx, -1);
                } else {
                    // Prime existed; find old extremes, then insert, then find new extremes
                    int oldL = *S.begin();
                    int oldR = *S.rbegin();
                    S.insert(idx);
                    int newL = *S.begin();
                    int newR = *S.rbegin();
                    if(newL != oldL) {
                        // cntL[oldL]--, cntL[newL]++
                        cntL[oldL]--;
                        range_add(oldL, -1);
                        cntL[newL]++;
                        range_add(newL, +1);
                    }
                    if(newR != oldR) {
                        // cntR[oldR]-- => V[t]++ for t>=oldR
                        cntR[oldR]--;
                        range_add(oldR, +1);
                        // cntR[newR]++ => V[t]-- for t>=newR
                        cntR[newR]++;
                        range_add(newR, -1);
                    }
                }
            }

            long long bestPrefixDiff = (M > 0 ? seg.getMax() : 0LL);
            long long ans = (long long)D + bestPrefixDiff;
            answer[qi] = (int)ans;
        }

        return answer;
    }
};

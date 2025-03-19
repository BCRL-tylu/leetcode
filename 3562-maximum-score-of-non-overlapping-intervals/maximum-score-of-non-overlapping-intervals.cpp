#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Interval {
    int l, r, w, orig;
};

struct State {
    // Total weight of chosen intervals.
    long long weight;
    // The chosen intervals' original indices, stored in sorted order.
    vector<int> seq;
};

// Compare two states: a is better than b if a has higher weight,
// or if equal weight then a.seq is lexicographically smaller.
bool better(const State &a, const State &b) {
    if(a.weight != b.weight)
        return a.weight > b.weight;
    return a.seq < b.seq;
}

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervalsInput) {
        int n = intervalsInput.size();
        // Build intervals with original indices.
        vector<Interval> intervals(n);
        for (int i = 0; i < n; i++) {
            intervals[i] = { intervalsInput[i][0], intervalsInput[i][1], intervalsInput[i][2], i };
        }
        // Sort by right endpoint. If equal, sort by left endpoint, then original index.
        sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
            if(a.r != b.r)
                return a.r < b.r;
            if(a.l != b.l)
                return a.l < b.l;
            return a.orig < b.orig;
        });
        
        // Precompute p: for each interval i in sorted order, find the largest index j < i 
        // with intervals[j].r < intervals[i].l.
        vector<int> p(n, -1);
        for (int i = 0; i < n; i++) {
            int lo = 0, hi = i - 1;
            int idx = -1;
            while(lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if(intervals[mid].r < intervals[i].l) {
                    idx = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            p[i] = idx;
        }
        
        // We can choose up to 4 intervals.
        const int MAXK = 4;
        const long long NEG_INF = -1e15;
        // dp[i][k]: best state using the first i intervals (in sorted order) with exactly k intervals chosen.
        // We use n+1 rows (i=0 means no intervals considered).
        vector<vector<State>> dp(n+1, vector<State>(MAXK+1, {NEG_INF, {}}));
        dp[0][0] = {0, {}}; // Base: no intervals chosen, weight 0.
        
        // Process intervals one by one in sorted order.
        for (int i = 1; i <= n; i++) {
            // Option 1: Do not take the (i-1)th interval.
            for (int k = 0; k <= MAXK; k++) {
                dp[i][k] = dp[i-1][k];
            }
            // Option 2: Take the (i-1)th interval.
            int j = i - 1;  // current interval index in sorted order
            // Find the previous state we can transition from:
            int prevIdx = (p[j] == -1 ? 0 : p[j] + 1);
            // Try to take the current interval for every valid count.
            for (int k = 1; k <= MAXK; k++) {
                if(dp[prevIdx][k-1].weight != NEG_INF) {
                    State candidate;
                    candidate.weight = dp[prevIdx][k-1].weight + intervals[j].w;
                    candidate.seq = dp[prevIdx][k-1].seq;
                    // Insert current interval's original index and sort the sequence.
                    candidate.seq.push_back(intervals[j].orig);
                    sort(candidate.seq.begin(), candidate.seq.end());
                    
                    if(better(candidate, dp[i][k])) {
                        dp[i][k] = candidate;
                    }
                }
            }
        }
        
        // Among all dp[n][k] for k = 0 .. MAXK, pick the best state.
        State bestState = {0, {}};
        for (int k = 0; k <= MAXK; k++) {
            if(better(dp[n][k], bestState)) {
                bestState = dp[n][k];
            }
        }
        sort(bestState.seq.begin(),bestState.seq.end());
        return bestState.seq;
    }
};

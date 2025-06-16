class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        constexpr int  INF_POS =  1e9 + 7;          // > any |nums[i]|
        constexpr int  INF_NEG = -INF_POS;          // < any nums[i]
        const int      n       = nums.size();

        /* ---------- 1. build suffix tables in O(n) ---------- */
        std::vector<int> maxPos(n, INF_NEG);   // largest ≥0
        std::vector<int> minPos(n, INF_POS);   // smallest ≥0
        std::vector<int> maxNeg(n, INF_NEG);   // largest negative (‑1 > ‑3)
        std::vector<int> minNeg(n, INF_POS);   // most‑negative number

        int curMaxPos = INF_NEG, curMinPos = INF_POS;
        int curMaxNeg = INF_NEG, curMinNeg = INF_POS;

        for (int i = n - 1; i >= 0; --i) {
            int v = nums[i];
            if (v >= 0) {
                curMaxPos = std::max(curMaxPos, v);
                curMinPos = std::min(curMinPos, v);
            } else {
                curMaxNeg = std::max(curMaxNeg, v);   // ‑1 > ‑4
                curMinNeg = std::min(curMinNeg, v);   // more negative
            }
            maxPos[i] = curMaxPos;
            minPos[i] = curMinPos;
            maxNeg[i] = curMaxNeg;
            minNeg[i] = curMinNeg;
        }

        /* ---------- 2. scan left‑to‑right in O(n) ------------ */
        long long best = LLONG_MIN;

        for (int i = 0; i + m - 1 < n; ++i) {
            int r = i + m - 1;          // first legal “last” index
            long long x = nums[i];

            if (x >= 0) {                                   // first number non‑negative
                if (maxPos[r] != INF_NEG)
                    best = std::max(best, x * maxPos[r]);   // + * +
                else if (maxNeg[r] != INF_NEG)
                    best = std::max(best, x * maxNeg[r]);   // + * –  (no + available)
            } else {                                        // first number negative
                if (minNeg[r] != INF_POS)
                    best = std::max(best, x * minNeg[r]);   // – * –  (positive product)
                else if (minPos[r] != INF_POS)
                    best = std::max(best, x * minPos[r]);   // – * +  (no – available)
            }
        }
        return best;
    }
};

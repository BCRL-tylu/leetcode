class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        const int n = points.size();
        long long left = 1, right = static_cast<long long>(*max_element(points.begin(), points.end())) * m;
        while (left <= right) {
            long long p = 0, c = m;
            const long long mid = (left + right) >> 1;
            for (int i = 0; i < n; ++i) {
                //mid / points[i] determines how many times points[i] must be added.
                // We ensure this number is rounded up using (mid + points[i] - 1) / points[i].
                const long long need = max((mid + points[i] - 1LL) / points[i] - p, 0LL);
                if (need) {
                // If need > 0, we spend moves to boost gameScore[i] to at least mid.
                // We update p to need - 1, tracking how far we have moved.
                // We reduce c (remaining moves) by need + p (spending moves for boosting and moving).
                    p = need - 1;
                    // -1 since the last more is the 'normal' progression
                    c -= need + p;
                    // minus the need and pass from totoal moves 
                } else if (i + 1 < n) {
                    // if no need, and not reach the end, set p to 0
                    p = 0;
                    // decrease c by 1 to simulate normal move
                    --c;
                }
                // if c < 0. break
                if (c < 0) break;
            }
            if (c >= 0) {
                // increase minimum when we can reach the mid
                left = mid + 1;
            } else {
                // decrease maximum with we cannot reach the mid 
                right = mid - 1;
            }
        }
        // minus one because we have left = mid + 1, and left > right, we need to make left =right, so 
        return right;
    }
};
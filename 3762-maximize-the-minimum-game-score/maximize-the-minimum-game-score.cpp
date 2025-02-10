class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        const int n = points.size();
        long long left = 1, right = static_cast<long long>(*max_element(points.begin(), points.end())) * m;
        while (left <= right) {
            long long p = 0, c = m;
            const long long mid = (left + right) >> 1;
            for (int i = 0; i < n; ++i) {
                const long long need = max((mid + points[i] - 1LL) / points[i] - p, 0LL);
                if (need) {
                    p = need - 1;
                    c -= need + p;
                } else if (i + 1 < n) {
                    p = 0;
                    --c;
                }
                if (c < 0) break;
            }
            if (c >= 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left - 1;
    }
};
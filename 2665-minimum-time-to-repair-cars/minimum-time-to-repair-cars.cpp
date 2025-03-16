class Solution {
public:
    long long repairCars(vector<int>& ranks, int cars) {
        long long l = 1, r = *min_element(ranks.begin(), ranks.end()) * (long long)cars * cars;

        while (l < r) {
            long long mid = (l + r) / 2;
            long long repaired = 0;

            for (int rnk : ranks) {
                repaired += (long long)sqrt(mid / rnk);
                if (repaired >= cars) break;  // Stop early if we have repaired enough cars
            }

            if (repaired >= cars) {
                r = mid;  // Try a smaller time
            } else {
                l = mid + 1;  // Increase time
            }
        }

        return l;
    }
};

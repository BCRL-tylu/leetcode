#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        int m = 1;
        while(m < n) m *= 2;
        vector<int> seg(2 * m, -1);
        
        for (int i = 0; i < n; i++) {
            seg[m + i] = baskets[i];
        }
        for (int i = m - 1; i > 0; i--) {
            seg[i] = max(seg[2 * i], seg[2 * i + 1]);
        }
        
        auto update = [&](int pos, int val) {
            pos += m;
            seg[pos] = val;
            for (pos /= 2; pos >= 1; pos /= 2) {
                seg[pos] = max(seg[2 * pos], seg[2 * pos + 1]);
            }
        };

        auto query = [&](int T) -> int {
            if (seg[1] < T) return -1;
            int idx = 1;
            while(idx < m) {
                if (seg[2 * idx] >= T) {
                    idx = 2 * idx;
                } else {
                    idx = 2 * idx + 1;
                }
            }
            return idx - m; 
        };
        
        int placed = 0;
        for (int f : fruits) {
            int idx = query(f);
            if (idx != -1) {
                placed++;
                update(idx, -1);
            }
        }
        return n - placed;
    }
};

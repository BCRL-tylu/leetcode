#include <vector>
#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>

using namespace std;

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        if (squares.empty()) return 0.0;

        struct Event {
            int y, type, x1, x2;
        };
        
        vector<Event> events;
        vector<int> xs;
        
        for (auto &sq : squares) {
            int x = sq[0], y = sq[1], l = sq[2];
            int x2 = x + l, y2 = y + l;
            events.push_back({y, +1, x, x2});
            events.push_back({y2, -1, x, x2});
            xs.push_back(x);
            xs.push_back(x2);
        }
        
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        
        sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
            return a.y < b.y;
        });

        int m = xs.size() - 1;
        vector<int> cover(4 * m, 0);
        vector<int> segLength(4 * m, 0);

        auto update = [&](int idx, int l, int r, int ql, int qr, int delta, auto&& update_ref) -> void {
            if (ql >= r || qr <= l) return;
            if (ql <= l && r <= qr) {
                cover[idx] += delta;
            } else {
                int mid = (l + r) / 2;
                update_ref(idx * 2, l, mid, ql, qr, delta, update_ref);
                update_ref(idx * 2 + 1, mid, r, ql, qr, delta, update_ref);
            }
            if (cover[idx] > 0) {
                segLength[idx] = xs[r] - xs[l];
            } else if (r - l == 1) {
                segLength[idx] = 0;
            } else {
                segLength[idx] = segLength[idx * 2] + segLength[idx * 2 + 1];
            }
        };

        vector<array<int64_t, 3>> segs;
        int last_y = events[0].y;
        int i = 0, nEvents = events.size();

        while (i < nEvents && events[i].y == last_y) {
            int ql = lower_bound(xs.begin(), xs.end(), events[i].x1) - xs.begin();
            int qr = lower_bound(xs.begin(), xs.end(), events[i].x2) - xs.begin();
            update(1, 0, m, ql, qr, events[i].type, update);
            i++;
        }

        while (i < nEvents) {
            int cur_y = events[i].y;
            if (cur_y > last_y) {
                int length = segLength[1];
                segs.push_back({last_y, cur_y, length});
                last_y = cur_y;
            }
            while (i < nEvents && events[i].y == cur_y) {
                int ql = lower_bound(xs.begin(), xs.end(), events[i].x1) - xs.begin();
                int qr = lower_bound(xs.begin(), xs.end(), events[i].x2) - xs.begin();
                update(1, 0, m, ql, qr, events[i].type, update);
                i++;
            }
        }

        int64_t T = 0;
        for (auto &s : segs)
            T += s[2] * (s[1] - s[0]);
        double target = T / 2.0;

        int M = segs.size();
        vector<int64_t> cum(M + 1, 0);
        for (int j = M - 1; j >= 0; j--) {
            int64_t area = segs[j][2] * (segs[j][1] - segs[j][0]);
            cum[j] = cum[j + 1] + area;
        }

        if (T == 0) return 0.0;
        if (target == T) return segs[0][0];

        double ans = 0.0;
        for (int j = 0; j < M; j++) {
            double F_start = cum[j];
            double F_end = cum[j + 1];
            if (F_start >= target && F_end <= target) {
                int L = segs[j][2];
                if (L == 0) {
                    ans = segs[j][0];
                } else {
                    ans = segs[j][1] - (target - cum[j + 1]) / double(L);
                }
                break;
            }
        }
        return ans;
    }
};

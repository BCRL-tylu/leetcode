class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        vector<long long> p;  // perimeter coordinates
        for (auto &pt : points) {
            int x = pt[0], y = pt[1];
            long long pos = 0;
            if (y == 0) {
                pos = x;
            } else if (x == side) {
                pos = side + y;
            } else if (y == side) {
                pos = 3LL * side - x;
            } else if (x == 0) {
                pos = 4LL * side - y;
            }
            p.push_back(pos);
        }
        sort(p.begin(), p.end());
        long long L = 4LL * side; // total perimeter

        // Binary search on the answer (the minimum gap d)
        long long lo = 0, hi = L, ans = 0;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (canPlaceK(p, k, mid, L)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return (int)ans;
    }
    
private:
    // Returns true if it's possible to pick k points with all gaps >= d.
    bool canPlaceK(const vector<long long>& p, int k, long long d, long long L) {
        int n = p.size();//number of points
        
        // Build extended array: [p[0], p[1], ..., p[n-1], p[0]+L, p[1]+L, ..., p[n-1]+L] to simulate the cycle
        vector<long long> ext(2 * n);
        for (int i = 0; i < n; i++){
            ext[i] = p[i];
            ext[i + n] = p[i] + L;
        }
        
        // Try every starting position in the original array.
        for (int start = 0; start < n; start++) {
            int count = 1;              // starting point chosen
            long long last = ext[start];
            int pos = start;
            // Try to greedily pick the next k-1 points using binary search.
            for (int i = 1; i < k; i++){
                // We only search up to ext.begin() + start + n,
                // which means we cover exactly one full circle.
                auto it = std::lower_bound(ext.begin() + start + 1, ext.begin() + start + n, last + d);
                if (it == ext.begin() + start + n) {
                    // Cannot find a valid next point.
                    count = i;  
                    break;
                }
                last = *it;
                pos = it - ext.begin();
                count++;
            }
            // After placing k points, also check that the gap from the last point 
            // back to the starting point (plus one full circle) is at least d.
            if (count >= k && (ext[start] + L - last) >= d)
                return true;
        }
        return false;
    }
};

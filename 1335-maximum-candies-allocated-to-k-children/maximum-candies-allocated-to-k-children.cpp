class Solution {
public:
    int maximumCandies(vector<int>& c, long long k) {
        int l = 1, r = 1e7, n = c.size(), mid;
        
        while (l <= r) { 
            mid = (l + r) >> 1; 
            long long kids = 0; 
            for (int i = 0; i < n; i++) kids += c[i] / mid;
            if (kids < k) { 
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return r; 
    }
};

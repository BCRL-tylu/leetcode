class Solution {
private:
    bool valid(int k, vector<int>& piles, int h) {
        int time = 0;
        for (int p : piles) {
            time += (p + k - 1) / k;  // Equivalent to ceil(p / k)
        }
        return time <= h;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1, r = *max_element(piles.begin(), piles.end());
        
        while (l < r) {
            int k = l + (r - l) / 2; // Prevent overflow
            if (valid(k, piles, h)) {
                r = k;
            } else {
                l = k + 1;
            }
        }
        return l; // or return r, since l == r at the end
    }
};

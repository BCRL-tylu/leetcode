class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& c, int k) {
        int n = c.size();
        int l = 0, r = 0, ans = 0;
        // mod_r tracks r % n so we don't recompute it each time
        int mod_r = 0;
        
        while(l < n) {
            // Try to extend the segment until its length is k or alternation fails.
            while(r - l + 1 < k) {
                // Instead of (r+1) % n, we use a conditional:
                int mod_next = (mod_r == n - 1) ? 0 : mod_r + 1;
                if(c[mod_r] != c[mod_next]) {
                    r++;
                    mod_r = mod_next;  // update mod_r to the new r modulo n
                } else {
                    break;
                }
            }
            if(r - l + 1 < k) {
                // If the current segment isn't long enough, skip to the next candidate segment.
                r++;
                // update mod_r using a conditional to avoid modulo call if possible
                mod_r = (r >= n) ? r - n : r;
                l = r;
            } else {
                // If a valid group of length k is found, count it and move the left pointer.
                l++;
                ans++;
            }
        }
        return ans;
    }
};

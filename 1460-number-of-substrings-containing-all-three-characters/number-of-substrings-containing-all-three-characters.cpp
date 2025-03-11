class Solution {
public:
    int numberOfSubstrings(string s) {
        int l = 0, r = 0,n = s.size(), ans = 0;
        vector<int> freq(3, 0);

        while(r < n) {
            freq[s[r]-'a']++;
            while(freq[0] > 0 && freq[1] > 0 && freq[2] > 0) {
                ans += n - r;
                freq[s[l]-'a']--;
                l++;
            }
            // Move to the next right index.
            r++;
        }
        return ans;
    }
};

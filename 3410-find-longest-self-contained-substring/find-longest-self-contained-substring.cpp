class Solution {
public:
    int maxSubstringLength(string s) {
        int n = s.size();
        vector<int> l(26, INT_MAX), r(26, -1);
        
        // Precompute the first and last occurrence of each letter.
        for (int i = 0; i < n; i++) {
            int id = s[i] - 'a';
            l[id] = min(l[id], i);
            r[id] = max(r[id], i);
        }
        
        int ans = -1;
       for (int i = 0; i < 26; i++) {
            // no such letter next
            if (l[i] == INT_MAX)  continue;
            int begin = l[i], last = r[s[begin]-'a'];

            for (int j = begin; j < n; j++) {
                char x = s[j]-'a';
                if (l[x] < begin) break; // X-begin-X-last, cannot have begin as begining of the substring

                last = max(last, r[x]); // begin-X-last-X or begin-X--X-last
                if (j == last && !(begin == 0 && j == n - 1)) ans = max(ans, j - begin + 1);
            }
        }
        return ans;
    }
};
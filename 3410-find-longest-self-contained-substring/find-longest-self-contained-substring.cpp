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
        // Only consider starting positions that are the first occurrence of their letter.
        for (int i = 0; i < n; i++) {
            if (i != l[s[i]-'a']) continue;
            
            int current_max = r[s[i]-'a'];
            // Try to extend the substring [i, j].
            for (int j = i; j < n; j++) {
                // If a letter appears that started before i, we must break.
                if (l[s[j]-'a'] < i)
                    break;
                current_max = max(current_max, r[s[j]-'a']);
                
                // When j reaches current_max, all letters in [i,j] have their full range inside.
                if (j == current_max) {
                    // Make sure it is not equal to the whole string.
                    if (!(i == 0 && j == n - 1))
                        ans = max(ans, j - i + 1);
                }
            }
        }
        
        return ans;
    }
};
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.size();
        
        const int ALPH = 26;
        vector<int> first(ALPH, n), last(ALPH, -1);

        // Step 1: Compute first and last occurrence of each character
        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';
            first[idx] = min(first[idx], i);
            last[idx] = max(last[idx], i);
        }

        // Step 2: Compute all valid "special substrings" as disjoint intervals
        vector<pair<int, int>> intervals;
        for (int c = 0; c < 26; c++) {
            if (first[c] == n) continue; // Character not in `s`
            
            int i = first[c], j = last[c];
            bool valid = true;

            for (int t = i; t <= j; t++) {
                int tidx = s[t] - 'a';
                if (first[tidx] < i) {
                    valid = false;
                    break;
                }
                j = max(j, last[tidx]);
            }

            if (valid && !(i == 0 && j == n - 1)) {
                intervals.push_back({i, j});
            }
        }

        // Step 3: Sort by start index
        sort(intervals.begin(), intervals.end());

        // Step 4: Use DP to compute maximum disjoint substrings
        int m = intervals.size();
        vector<int> dp(m + 1, 0);

        for (int i = m - 1; i >= 0; i--) {
            int next = i + 1;
            while (next < m && intervals[next].first <= intervals[i].second) {
                next++;
            }
            dp[i] = max(dp[i + 1], 1 + dp[next]);
        }

        return dp[0] >= k;
    }
};
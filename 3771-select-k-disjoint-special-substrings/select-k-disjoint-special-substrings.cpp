class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.size();

        const int ALPH = 26;
        vector<int> first(ALPH, n), last(ALPH, -1);

        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';
            first[idx] = min(first[idx], i);
            last[idx] = max(last[idx], i);
        }
        vector<pair<int, int>> intervals;
        for (int c = 0; c < 26; c++) {
            if (first[c] == n) continue; // Character not in `s`
            int i = first[c], j = last[c];
            bool valid = true;

            // for this letter we go from first to last
            for (int t = i; t <= j; t++) {
                int tidx = s[t] - 'a'; // get the char between first and last
                if (first[tidx] < i) { // if we have something like x-first-x-last, the this first cannot be the start of a special substring
                    valid = false;
                    break;
                }
                // if we have somehing like first-x-last-x or first-x-x-last, we greedy the range, since we cannot have another interval between first and max(last, last[middle])
                j = max(j, last[tidx]);
            }
            if (valid && !(i == 0 && j == n - 1)) {
                intervals.push_back({i, j});
            }
        }

        sort(intervals.begin(), intervals.end());

        int m = intervals.size();
        vector<int> dp(m + 1, 0);

        for (int i = 0; i < m; i++) {
            int next = i + 1;
            dp[next] = dp[i]; // Option 1: Skip this interval
            while (next < m && intervals[next].first <= intervals[i].second) {
                next++; // Find the next non-overlapping interval, increase next until the intervels[next] dont overlapp with current
            }
            dp[next] = max(dp[next], dp[i] + 1); // Option 2: Take this interval
        }
        return dp[m] >= k;
    }
};
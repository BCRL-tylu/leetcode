class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.size();
        if(n == 0) return false;
        
        // Precompute first and last occurrence for each character.
        const int ALPH = 26;
        vector<int> first(ALPH, n), last(ALPH, -1);
        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';
            first[idx] = min(first[idx], i);
            last[idx] = max(last[idx], i);
        }
        
        // For each index i, compute candidate interval [i, cand[i]]
        // if i is a valid start of a special substring.
        // A valid start must be the first occurrence of s[i].
        // For repeated letters the candidate is determined by "expanding"
        // as in partition-labels; for a unique letter, the candidate is [i, i].
        vector<int> cand(n, -1);
        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';
            // Only a first occurrence can start a special substring.
            if(i != first[idx])
                continue;
            
            // Start candidate at i.
            int j = last[idx];
            bool valid = true;
            // Expand candidate interval
            for (int t = i; t <= j; t++) {
                int tidx = s[t] - 'a';
                // If any letter in s[i..j] started before i, then s[i..j] is not special.
                if(first[tidx] < i) { 
                    valid = false;
                    break;
                }
                j = max(j, last[tidx]);
            }
            // Do not allow the candidate to be the entire string.
            if(valid && !(i == 0 && j == n - 1)) {
                cand[i] = j;
            }
        }
        
        // dp[i] = max number of disjoint special substrings from s[i..n-1].
        vector<int> dp(n+1, 0);
        for (int i = n - 1; i >= 0; i--) {
            // Option 1: skip index i.
            dp[i] = dp[i+1];
            // Option 2: if a valid candidate starts at i, pick it.
            if(cand[i] != -1) {
                dp[i] = max(dp[i], 1 + dp[cand[i] + 1]);
            }
        }
        
        return dp[0] >= k;
    }
};


class Solution {
private:
    // Memoization table
    vector<vector<int>> memo;

    // Helper recursive function
    bool matchHelper(const string& s, const string& p, int i, int j) {
        // Check memoization table
        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        // (1) If we reach the end of the pattern, it's a match
        if (j == p.size()) {
            return memo[i][j] = true;
        }

        // (2) If we reach the end of `s` but not the pattern, it's not a match
        if (i == s.size() && p[j]!= '*') {
            return memo[i][j] = false;
        }

        if (i == s.size() && p[j]== '*' && j == p.size()-1) {
            return memo[i][j] = true;
        }
        // (3) Handle '*' in the pattern
        if (p[j] == '*') {
            // Try to match '*' with zero or more characters in `s`
            for (int k = i; k <= s.size(); k++) {
                if (matchHelper(s, p, k, j + 1)) {
                    return memo[i][j] = true;
                }
            }
        } else {
            // (4) Match the current characters
            if (s[i] == p[j]) {
                return memo[i][j] = matchHelper(s, p, i + 1, j + 1);
            }
        }

        return memo[i][j] = false; // No match found
    }

public:
    bool hasMatch(string s, string p) {
        // Initialize memoization table
        memo = vector<vector<int>>(s.size() + 1, vector<int>(p.size() + 1, -1));

        // Try matching `p` starting at every position in `s`
        for (int start = 0; start <= s.size(); start++) {
            if (matchHelper(s, p, start, 0)) {
                return true;
            }
        }

        return false;
    }
};

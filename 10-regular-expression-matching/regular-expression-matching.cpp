#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    vector<vector<int>> memo; // Memoization table

    // Recursive helper function
    bool matchHelper(const string& s, const string& p, int i, int j) {
        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        // Base case: if both strings are fully matched
        if (i == s.size() && j == p.size()) {
            return memo[i][j] = true;
        }

        // If the pattern is exhausted but the string is not
        if (j == p.size()) {
            return memo[i][j] = false;
        }

        // Check if the first character matches or if it's '.'
        bool firstMatch = (i < s.size() && (s[i] == p[j] || p[j] == '.'));

        // Handle '*' in the pattern
        if (j + 1 < p.size() && p[j + 1] == '*') {
            // Skip the '*' (zero occurrences of preceding element) or use it (consume one character)
            memo[i][j] = matchHelper(s, p, i, j + 2) || (firstMatch && matchHelper(s, p, i + 1, j));
        } else {
            // Regular character match or '.'
            memo[i][j] = firstMatch && matchHelper(s, p, i + 1, j + 1);
        }

        return memo[i][j];
    }

public:
    bool isMatch(string s, string p) {
        // Initialize memoization table
        memo = vector<vector<int>>(s.size() + 1, vector<int>(p.size() + 1, -1));
        return matchHelper(s, p, 0, 0);
    }
};

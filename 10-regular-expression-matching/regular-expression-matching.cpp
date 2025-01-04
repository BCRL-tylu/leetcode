#include <unordered_map>
#include <string>
#include <functional>
using namespace std;

class Solution {
private:
    unordered_map<string, bool> memo; // Memoization map

    // Recursive helper function
    bool matchHelper(const string& s, const string& p, int i, int j) {
        // Create a unique key for the current state
        string key = to_string(i) + "," + to_string(j);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }

        // Base case: if both strings are fully matched
        if (i >= s.size() && j >= p.size()) {
            return memo[key] = true;
        }

        // If the pattern is exhausted but the string is not
        if (j >= p.size()) {
            return memo[key] = false;
        }

        // Check if the first character matches or if it's '.'
        bool firstMatch = (i < s.size() && (s[i] == p[j] || p[j] == '.'));

        // Handle '*' in the pattern
        if (j + 1 < p.size() && p[j + 1] == '*') {
            // Skip the '*' (zero occurrences of preceding element) or use it (consume one character)
            memo[key] = matchHelper(s, p, i, j + 2) || (firstMatch && matchHelper(s, p, i + 1, j));
            return memo[key];
        }

        // Regular character match or '.'
        if (firstMatch) {
            memo[key] = matchHelper(s, p, i + 1, j + 1);
            return memo[key];
        }

        return memo[key] = false; // No match
    }

public:
    bool isMatch(string s, string p) {
        // Clear the memoization map before starting a new match
        memo.clear();
        return matchHelper(s, p, 0, 0);
    }
};

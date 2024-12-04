#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    char nextCharCyclic(char ch) {
        return (ch - 'a' + 1) % 26 + 'a'; // Direct cyclic calculation, assumes valid 'a'-'z'.
    }

    bool canMakeSubsequence(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        int cp = 0;

        for (int i = 0; i < m; ++i) {
            bool found = false;
            while (cp < n) {
                if (str2[i] == str1[cp] || nextCharCyclic(str1[cp]) == str2[i]) {
                    ++cp; // Move cp forward to avoid re-checking.
                    found = true;
                    break;
                }
                ++cp; // Skip the unmatched character.
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }
};

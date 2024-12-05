#include <string>
#include <iostream>

class Solution {
public:
    bool canChange(std::string start, std::string target) {
        int n = start.size();
        int sp = 0; // Pointer for start
        int tp = 0; // Pointer for target

        while (sp < n && tp < n) {
            // Skip underscores in start
            while (sp < n && start[sp] == '_') {
                sp++;
            }
            // Skip underscores in target
            while (tp < n && target[tp] == '_') {
                tp++;
            }

            // If both pointers are at the end, it means we've matched all
            if (sp == n && tp == n) {
                return true;
            }

            // If we reached the end of one but not the other, return false
            if (sp == n || tp == n) {
                return false;
            }

            // Check if characters match
            if (start[sp] != target[tp]) {
                return false; // Mismatched characters
            }

            // Check the direction of movement for 'L' and 'R'
            if (start[sp] == 'L') {
                // 'L' should not move to the right
                if (sp < tp) {
                    return false; // Invalid move
                }
            } else if (start[sp] == 'R') {
                // 'R' should not move to the left
                if (sp > tp) {
                    return false; // Invalid move
                }
            }

            // Move to the next character
            sp++;
            tp++;
        }
        
        // Check if we have valid characters left
        while (sp < n && start[sp] == '_') {
            sp++;
        }
        while (tp < n && target[tp] == '_') {
            tp++;
        }
        
        return sp == n && tp == n; // Both pointers should be at the end
    }
};


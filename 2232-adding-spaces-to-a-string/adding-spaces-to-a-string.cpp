#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string addSpaces(std::string s, std::vector<int>& spaces) {
        int k = spaces.size();
        std::string rt; // Resulting string
        int prev = 0;   // To track the last position in the string

        // Loop through the spaces vector
        for (int i = 0; i < k; ++i) {
            // Append the substring from prev to the current space index
            rt += s.substr(prev, spaces[i] - prev); // Get substring from prev to spaces[i]
            rt += " "; // Add a space
            prev = spaces[i]; // Update previous position to current space index
        }

        // Append the remaining part of the string after the last space
        rt += s.substr(prev);

        return rt;
    }
};
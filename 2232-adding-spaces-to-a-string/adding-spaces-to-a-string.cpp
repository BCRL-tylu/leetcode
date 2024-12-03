#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string addSpaces(std::string s, std::vector<int>& spaces) {
        std::string rt; // Resulting string
        rt.reserve(s.length() + spaces.size()); // Reserve memory for efficiency

        const char* ptr = s.c_str(); // Get a pointer to the string data
        int prev = 0; // To track the last position

        for (int spaceIndex : spaces) {
            // Append the substring from prev to the current space index
            rt.append(ptr + prev, spaceIndex - prev); // Directly append using pointers
            rt += ' '; // Add a space
            prev = spaceIndex; // Update previous position to current space index
        }

        // Append the remaining part of the string after the last space
        rt.append(ptr + prev); // Append remaining characters directly

        return rt;
    }
};
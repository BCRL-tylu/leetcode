#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string addSpaces(std::string s, std::vector<int>& spaces) {
        // Calculate the size of the new string
        int total_length = s.length() + spaces.size();
        std::string rt(total_length, ' '); // Preallocate with total size and fill with spaces
        
        int prev = 0; // Last processed position
        int rt_index = 0; // Index for the resulting string

        // Iterate through the spaces and build the result
        for (int spaceIndex : spaces) {
            // Copy characters from the original string to the result string
            while (prev < spaceIndex) {
                rt[rt_index++] = s[prev++]; // Copy character from s to rt
            }
            rt[rt_index++] = ' '; // Add space
        }

        // Copy remaining characters from s after the last space
        while (prev < s.length()) {
            rt[rt_index++] = s[prev++];
        }
        return rt;
    }
};
#include <string>
#include <algorithm>

class Solution {
public:
    std::string answerString(std::string word, int f) {
        if (f == 1) return word;

        char maxChar = 'a'; // Maximum character in the word
        int length = word.size();
        int subLength = length - f + 1; // Length of the substring to be formed
        std::string result = "";

        // Find the maximum character in the word
        for (char ch : word) {
            maxChar = std::max(maxChar, ch);
        }

        std::string largestSub = "";  // To keep track of the largest substring
        int largestSubEnd = 0;        // To track the ending index of the largest substring

        // Traverse the string to find substrings starting with maxChar
        for (int i = 0; i < length; i++) {
            if (word[i] == maxChar) {
                std::string currentSub = "";
                currentSub += maxChar;

                // Keep appending elements until we reach the limit
                while (i + 1 < length && currentSub.size() < std::min(subLength, length - i) &&
                       (word[i + 1] != maxChar || currentSub.back() == maxChar)) {
                    currentSub += word[++i];
                }

                // Update the largest substring if the current one is better
                if (currentSub > largestSub) {
                    largestSub = currentSub;
                    largestSubEnd = i;
                }
            }
        }

        int largestSubSize = largestSub.size();
        std::string remainingSub = word.substr(largestSubEnd + 1, std::min(subLength - largestSubSize, length - largestSubEnd));
        result = largestSub + remainingSub;

        return result; // Return the result trimmed to the desired size
    }
};

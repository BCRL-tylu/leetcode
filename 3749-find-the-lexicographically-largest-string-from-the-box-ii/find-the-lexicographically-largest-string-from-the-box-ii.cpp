#include <string>
#include <algorithm>

class Solution {
public:
    std::string answerString(std::string word, int numFriends) {
        char maxchar = 'a'; // Renamed from maxm to maxchar
        int n = word.size();
        if (numFriends == 1) return word;

        int k = n - numFriends + 1;
        std::string ans = "";

        // Find the maximum character in the word
        for (char c : word) {
            maxchar = std::max(maxchar, c); // Updated variable name
        }
        
        std::string maxstring = "";  // To keep track of the largest substring
        int start_index = 0;         // To track the starting index of the max substring
        
        // Traverse the string to find substrings starting with maxchar
        for (int i = 0; i < n; i++) {
            if (word[i] == maxchar) {
                std::string temp_ans = "";
                temp_ans += maxchar; // Updated variable name
                
                // Collect characters while the conditions hold
                while (i + 1 < n && temp_ans.size() < std::min(k, n - i) && (word[i + 1] != maxchar || temp_ans.back() == maxchar)) {
                    temp_ans += word[++i];
                }
                
                // Compare temp_ans with current largest substring
                if (temp_ans > maxstring) {
                    maxstring = temp_ans; // Update the largest substring
                    start_index = i;      // Update the index of the largest substring
                }
            }
        }
        
        // Build the answer based on the largest substring found
        int sz = maxstring.size();
        std::string temp_add = word.substr(start_index + 1, std::min(k - sz, n - start_index));
        ans = maxstring + temp_add; // Combine the largest substring with the additional characters
        
        return ans; // Return the result trimmed to size k
    }
};

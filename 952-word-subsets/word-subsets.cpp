#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        unordered_map<char, int> w2m; // Maximum frequency of each letter across words2

        // Build the maximum frequency map for words2
        for (const string& word : words2) {
            unordered_map<char, int> current_map;
            for (char c : word) {
                current_map[c]++;
                w2m[c] = max(w2m[c], current_map[c]);
            }
        }

        vector<string> ans;

        // Check each word in words1
        for (const string& word : words1) {
            unordered_map<char, int> current_map;
            for (char c : word) {
                current_map[c]++;
            }

            // Check if word satisfies the maximum frequency constraints
            bool isUniversal = true;
            for (const auto& [key, value] : w2m) {
                if (current_map[key] < value) {
                    isUniversal = false;
                    break;
                }
            }

            if (isUniversal) {
                ans.push_back(word);
            }
        }

        return ans;
    }
};

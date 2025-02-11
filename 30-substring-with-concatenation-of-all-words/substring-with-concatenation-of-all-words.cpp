#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        if(s.empty() || words.empty()) return ans;
        
        int wordLen = words[0].size();
        int wordCount = words.size();
        int totalLen = wordLen * wordCount;
        if(s.size() < totalLen) return ans;
        
        // Map each distinct word to an id and count its frequency.
        unordered_map<string, int> wordToId;
        int idCounter = 0;
        for(const string &w : words) {
            if(wordToId.find(w) == wordToId.end())
                wordToId[w] = idCounter++;
        }
        int distinctCount = idCounter;
        // target frequency for each distinct word id.
        vector<int> target(distinctCount, 0);
        for(const string &w : words) {
            target[wordToId[w]]++;
        }
        
        // For every index in s, record the id of the word that starts at that index,
        // or -1 if none of our words occurs there.
        int n = s.size();
        vector<int> wordMatch(n, -1);
        // For each distinct word, use the Z algorithm to find its occurrences in s.
        for (auto &entry : wordToId) {
            const string &w = entry.first;
            int wordId = entry.second;
            // Build a string of the form:  pattern + '$' + s
            string combined = w + '$' + s;
            vector<int> z = computeZ(combined);
            int wSize = w.size();  // equals wordLen
            // In the combined string, positions after index (wSize) + 1 correspond to positions in s.
            for (int i = wSize + 1; i < (int)combined.size(); i++) {
                if (z[i] == wSize) {
                    int pos = i - (wSize + 1);
                    // Mark this position as a match with word id 'wordId'.
                    wordMatch[pos] = wordId;
                }
            }
        }
        
        // Now, for each starting offset (mod wordLen) use a sliding window.
        // (This is similar to the standard solution that slides over words.)
        for (int offset = 0; offset < wordLen; offset++) {
            int left = offset;
            int count = 0;  // count of words in the current window
            vector<int> currCount(distinctCount, 0);
            
            // Step through s in increments of wordLen.
            for (int j = offset; j <= n - wordLen; j += wordLen) {
                int id = wordMatch[j];
                if (id != -1) {
                    currCount[id]++;
                    count++;
                    // If we have too many of this word, slide the window forward.
                    while (currCount[id] > target[id]) {
                        int leftId = wordMatch[left];
                        currCount[leftId]--;
                        left += wordLen;
                        count--;
                    }
                    // When the window size equals the number of words, we found a valid index.
                    if (count == wordCount) {
                        ans.push_back(left);
                        // Slide the window by one word.
                        int leftId = wordMatch[left];
                        currCount[leftId]--;
                        left += wordLen;
                        count--;
                    }
                } else {
                    // Reset the window if this segment does not match any word.
                    currCount.assign(distinctCount, 0);
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        
        return ans;
    }
    
private:
    // Standard Z-algorithm that computes the Z-array for a string.
    // z[i] = the length of the longest substring starting at i that matches the prefix.
    vector<int> computeZ(const string &str) {
        int n = str.size();
        vector<int> z(n, 0);
        int l = 0, r = 0;
        for (int i = 1; i < n; i++) {
            if (i <= r)
                z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < n && str[z[i]] == str[i + z[i]])
                z[i]++;
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }
};

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        if (s.empty() || words.empty()) return ans;

        int wordLen = words[0].size(), wordCount = words.size(), totalLen = wordLen * wordCount, n = s.size();
        if (n < totalLen) return ans;

        unordered_map<string, int> wordFreq;
        for (const string& w : words) wordFreq[w]++;

        for (int offset = 0; offset < wordLen; offset++) {
            unordered_map<string, int> windowFreq;
            int left = offset, count = 0;

            for (int j = offset; j + wordLen <= n; j += wordLen) {
                string word = s.substr(j, wordLen);
                if (wordFreq.count(word)) {
                    windowFreq[word]++;
                    count++;
                    while (windowFreq[word] > wordFreq[word]) {
                        windowFreq[s.substr(left, wordLen)]--;
                        left += wordLen;
                        count--;
                    }
                    if (count == wordCount) {
                        ans.push_back(left);
                    }
                } else {
                    windowFreq.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        return ans;
    }
};
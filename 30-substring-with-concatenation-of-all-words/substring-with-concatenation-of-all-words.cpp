class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string,int> wordsToCount;
        unordered_map<string,int> seen;
        int wordLen = words[0].size();
        int wordCount = words.size();
        int n = s.size();
        vector<int> result;
        for(string &word:words) {
            wordsToCount[word]++;
        }
        for(int i =0;i<wordLen;i++) {
            int wordLeft = wordCount;
            seen.clear();
            for(int left = i,right=i;right<=(n-wordLen);right+=wordLen) {
                string target = s.substr(right,wordLen);
                if(!wordsToCount.count(target)) {
                    seen.clear();
                    left = right + wordLen;
                    wordLeft = wordCount;
                }else {
                    seen[target]++;
                    while(seen[target]>wordsToCount[target]) {
                        string removed = s.substr(left,wordLen);
                        seen[removed]--;
                        wordLeft++;
                        left+=wordLen;
                    }
                    wordLeft--;
                }
                if(wordLeft==0) {
                    result.push_back(left);
                }
            }
        }
        return result;
    }
};
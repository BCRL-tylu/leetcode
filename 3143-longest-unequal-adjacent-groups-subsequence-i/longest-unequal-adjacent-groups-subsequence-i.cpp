class Solution {
public:
    vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {
        int n=words.size(),i;
        vector<string> ans;
        ans.emplace_back(words[0]);
        int presentNum=groups[0];
        for(i=1;i<n;i++){
            if(groups[i]!=presentNum){
                ans.emplace_back(words[i]);
                presentNum=groups[i];
            }
        }
        return ans; 
    }
};
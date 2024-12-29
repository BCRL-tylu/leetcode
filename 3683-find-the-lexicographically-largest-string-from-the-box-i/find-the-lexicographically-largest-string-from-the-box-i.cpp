class Solution {
public:
    string answerString(string word, int numFriends) {
        char maxm = 'a';
        if(numFriends == 1)return word;
        int n = word.size(),k = n-numFriends+1;
        string ans = "a";
        for(auto itr : word)maxm = max(maxm,itr);
        for(int i = 0;i < n;i++){
            if(word[i] == maxm)ans = max(ans,word.substr(i,min(k,n-i)));
        }
        return ans;
    }
};
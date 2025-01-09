class Solution {
public:
    int prefixCount(vector<string>& words, string pref) {
        int ans = 0;
        for(int i =0;i<words.size();i++){
            string s = words[i];
            if(s.find(pref) ==0)ans++;
        }
        return ans;
    }
};
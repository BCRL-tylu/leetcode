//bcrl-tylu count the number of odd letter sets
class Solution {
public:
    bool canConstruct(string s, int k) {
        int sz = s.size();
        if(sz<k) return false;
        vector<int> lc(26);
        for(int i = 0;i<sz;i++){
            lc[s[i]-'a']++;
        }
        int odcount = 0;
        for(int i = 0; i<26;i++){
            if(lc[i] % 2) odcount++;
        }
        if(odcount >k) return false;
        return true;
    }
};
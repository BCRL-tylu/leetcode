class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        vector<string> ans;
        int i=0, l=k-1, n = s.size();
        while(i+l<n){
            ans.push_back(s.substr(i,k));
            i+=k;
        }
        if(i>=n) return ans;
        string temp = s.substr(i);
        while(temp.size()<k){
            temp.push_back(fill);
        }
        ans.push_back(temp);
        return ans;
    }
};
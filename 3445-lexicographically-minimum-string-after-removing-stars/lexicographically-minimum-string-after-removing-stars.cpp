class Solution {
public:
    string clearStars(string s) {
        vector<priority_queue<int>> vpq(26);
        int n=s.size();
        for(int i =0;i<n;i++){
            if(s[i]=='*'){
                for(int i=0;i<26;i++){
                    if(!vpq[i].empty()){
                        int u = vpq[i].top(); vpq[i].pop();
                        s[u] = '.';
                        break;
                    }
                }
            }else{
                vpq[s[i]-'a'].push(i);
            }
        }
        string ans;
        for(auto k:s){
            if(k=='.'||k=='*') continue;
            ans.push_back(k);
        }
        return ans;
    }
};
class Solution {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<int,int> visited;
        vector<int> cha(26,0),ans;
        int cnt =0,cc=0;
        for(int i =0;i<s.size();i++){
            visited[s[i]-'a']++;
        }
        for(int i =0;i<s.size();i++){
            int ind = s[i]-'a';
            cnt++;
            bool cut = true;
            if(cha[ind] ==0) cha[ind]++;
            if(--visited[ind]==0){
                cha[ind] =0;
                for(int i =0;i<26;i++){
                    if(cha[i]==1){
                        cut = false;
                        break;
                    }
                }
                if(cut){
                    ans.push_back(cnt);
                    cnt=0;
                }
            }
        }
        return ans;
    }
};
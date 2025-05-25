class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        vector<vector<int>> mat(26,vector<int>(26));
        int  n =words.size(),ans=0,maxmid=0;
        for(int i = 0;i<n;i++){
            int f = words[i][0]-'a',s=words[i][1]-'a';
            if(mat[s][f]>0){
                ans+=4;
                mat[s][f]--;
                continue;
            }
            mat[f][s]++;

        }
        for(int i =0;i<26;i++){
            maxmid = max(maxmid,mat[i][i]);
        }
        return ans+maxmid*2;
    }
};
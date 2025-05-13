class Solution {
public:
    int lengthAfterTransformations(string s, int t) {
        int ans=s.size(),mod=1e9+7;
        vector<int> m(26,0);
        for(char k:s) m[k-'a']++;
        
        for(int i=0;i<t;i++){
            vector<int> tempm(26,0);
            for(int j=0;j<25;j++){
                tempm[j+1]+=m[j]%mod;
            }
            int addtion = m[25]%mod;
            ans= (ans%mod+addtion%mod)%mod;
            tempm[0]+=addtion%mod;
            tempm[1]+=addtion%mod;
            m=tempm;
        }
        return ans;
    }
};
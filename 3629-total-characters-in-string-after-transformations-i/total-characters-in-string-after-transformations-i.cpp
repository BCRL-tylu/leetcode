class Solution {
public:
    int lengthAfterTransformations(string s, int t) {
        int ans = 0, mod = 1e9 + 7;
        vector<int> m(26, 0);
        for (char c : s) m[c - 'a']++;

        while (t--) {
            int z = m[25];  
            for (int i = 24; i >= 0; --i)m[i+1] = m[i];
            m[0]= z%mod;
            m[1]=(m[1]+z)%mod;
        }
        for (int i = 0; i <26;i++) ans=(ans+m[i])%mod;
        return ans;
    }
};

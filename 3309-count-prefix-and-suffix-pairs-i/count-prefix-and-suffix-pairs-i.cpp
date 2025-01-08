
class Solution {
public:
    
    vector<int> zFun(string &s) {
        int n = s.length();
        vector<int> z(n, 0);
        int l = 0, r = 0;
        for(int i=1; i<n; i++)  {
            if(i < r)   z[i] = min(r-i, z[i-l]);
            while(i+z[i] < n && s[i+z[i]] == s[z[i]])   z[i]++;
            if(i+z[i] > r)  l = i, r = i + z[i];
        }
        return z;
    }
    
    long long countPrefixSuffixPairs(vector<string>& words) {
        long long ans = 0;
        unordered_map<string, long long> mp;
        unordered_set<int> count;
        
        for(auto &s : words)    {
            vector<int> z = zFun(s);
            int n = s.length();
            for(int i=1; i<n; i++)  {
                if(i+z[i] == n && count.find(z[i]) != count.end())  {
                    string temp = s.substr(0, z[i]);
                    ans += mp[temp];
                }
            }
            if(mp.find(s) != mp.end())
                ans += mp[s];
            mp[s]++;
            count.insert(n);
        }
        
        return ans;
    }
};

/*

["a","aba","ababa","aa"]
["pa","papa","ma","mama"]
["abab","ab"]
["a","a"]
["a","aa","aa","b","ab"]
["bcc","c","cbaaa","ba","cabbc","b","bcbb","baca","caa","aa","caa","ca","cacac"]

*/

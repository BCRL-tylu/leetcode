class Solution {
public:
    string smallestNumber(string pattern) {
        string ans;
        int n = pattern.size(), r;
        for (int i = 1; i <= n + 1; i++)
            ans += i + '0';
        
        for (int i = 0; i < n; i++) {
            if (pattern[i] == 'D') {
                int l = i;
                while (i < n && pattern[++i] == 'D') {}
                reverse(ans.begin()+l,ans.begin()+i+1);
                if(i ==n-1) break;
                i--;
            }
        }
        return ans;
    }
};
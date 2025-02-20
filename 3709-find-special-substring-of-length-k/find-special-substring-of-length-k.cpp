class Solution {
public:
    bool hasSpecialSubstring(string s, int k) {
        int c , n=s.size(),i=0;
        for(;i<n;i++){
            c = 1;
            while(i<n-1 && s[i+1] == s[i]){
                i++;
                c++;
            }
            if(c == k){
                return true;
            }
        }
        return false;
    }
};
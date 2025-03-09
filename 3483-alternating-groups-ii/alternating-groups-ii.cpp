class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& c, int k) {
        int n = c.size(),l = 0,r=0,ans=0,tr;

        while(l<n){
            tr = r+1;
            while(tr-l<k && c[r%n]!=c[(tr)%n]){
                tr = ++r+1;
            }
            if(tr-l<k){
                r++;
                l=r;
            }else{
                l++;
                ans++;
            }
        }
        return ans;
    }
};
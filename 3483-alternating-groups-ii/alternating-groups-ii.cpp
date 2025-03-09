class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& c, int k) {
        int n = c.size(),l = 0,r=0,ans=0,tr;

        while(l<n){
            while(r-l+1<k && c[r%n]!=c[(r+1)%n]){
                tr = ++r+1;
            }
            if(r-l+1<k){
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
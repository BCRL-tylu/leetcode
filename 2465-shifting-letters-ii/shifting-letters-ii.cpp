class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int sz = s.size();
        vector<int> range(sz+1,0);
        int n = shifts.size();
        int ma =INT_MIN,mi = INT_MAX;
        for(int i =0; i<n;i++){
            int l = shifts[i][0], r = shifts[i][1],dir = shifts[i][2];
            ma = max(r,ma);
            mi = min(l,mi);
            if(dir==0){
                range[l]-=1;
                range[r+1]+=1;
            }else{
                range[l]+=1;
                range[r+1]-=1;
            }
        }

        int current=0;
        for(int i = 0; i<sz;i++){
            current+= range[i];
            s[i] = 'a' + ((s[i] - 'a' + current) % 26 + 26) % 26;

        }
        return s;
    }
};
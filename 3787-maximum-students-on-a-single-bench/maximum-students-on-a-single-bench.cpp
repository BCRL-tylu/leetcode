const int sz =101;
class Solution {
public:
    int maxStudentsOnBench(vector<vector<int>>& st) {
        if(st.size()==0) return 0;
        int hm[sz][sz] = {},k[sz] = {},ans = INT_MIN;
        for(auto& r:st){
            int s = r[0], b =r[1];
            if(hm[s][b])continue;
            hm[s][b]++;
            ans = max(ans,++k[b]);
        }
        return ans;
    }
};
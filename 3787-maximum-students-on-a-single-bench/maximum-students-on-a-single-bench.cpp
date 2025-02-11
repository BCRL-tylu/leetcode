class Solution {
public:
    int maxStudentsOnBench(vector<vector<int>>& s) {
        if(s.size()==0) return 0;
        unordered_map<int,set<int>> hm;
        int ans = INT_MIN;
        for(auto& r:s){
            hm[r[1]].insert(r[0]);
            ans = std::max(ans,(int)hm[r[1]].size());
        }
        return ans;
    }
};
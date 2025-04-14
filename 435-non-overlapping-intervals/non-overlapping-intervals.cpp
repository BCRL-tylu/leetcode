class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](const vector<int>& a, const vector<int>& b) {
        return a.back() < b.back();
    });
    int ed = intervals[0][1],ans =1;
    for(int i =1; i<intervals.size();i++){
        if(intervals[i][0]>=ed){
            ed = intervals[i][1];
            ans++;
        }
    }
    return intervals.size()-ans;
    }
};
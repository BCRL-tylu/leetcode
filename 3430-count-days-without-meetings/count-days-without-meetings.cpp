class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        sort(meetings.begin(),meetings.end());
        for(int i=0;i<meetings.size();i++){
            int l = meetings[i][0];
            int r = meetings[i][1];
            while(i<meetings.size()-1 && (meetings[i+1][0]<=r)){
                r=max(r,meetings[i+1][1]);
                i++;
            }
            days -= r-l+1;
        }
        return days;
    }
};
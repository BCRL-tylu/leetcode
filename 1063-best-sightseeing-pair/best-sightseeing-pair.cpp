class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int n = values.size();
        int max_rt = INT_MIN;
        int ma = values[n-1]-n+1;
        for(int i=n-2;i>=0;i--){
           ma = max(ma, values[i+1]-i-1);
           max_rt =max(max_rt,values[i]+i+ma);
        }
        return max_rt;
    }
};
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        long long mi=0,ma = 0,inti = 0;
        for(int k:differences){
            inti+=(long long)k;
            mi = min(mi,inti);
            ma = max(ma,inti);
        }
        return (int)max((mi-lower)+(upper-ma)+1,(long long)0);
    }
};
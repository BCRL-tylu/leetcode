class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        
        int res = 0  , imax =0  ;
        for(int a : values){
            res =  max(res ,  imax +  a);
            imax =  max(imax ,  a )  -1 ; 
        }
        
        return res ;
        
    }
};
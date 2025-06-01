class Solution {
public:
    long long distributeCandies(int n, int limit) {
        long long ans =0;
        for(int i =max(0,n-2*limit);i<=min(n,limit);i++){
            long long left =(long long)n-i;
            if(left>=limit){
                ans+=(long long)2*limit-left+1;
            }else{
                ans+=(long long)left+1;
            }
        }
        return ans;
    }
};
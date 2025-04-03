class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
                long long ans=INT_MIN, n=nums.size();
        long long i =0, k=0;
        vector<long long> ma(n,0);
        ma[n-1] = nums[n-1];
        for(long long k=n-2;k>=0;k--){
            ma[k] = max((long long)nums[k],ma[k+1]);
        }
        for(long long j=1;j<n-1;j++){
            i = max(i,(long long)nums[j-1]);
            ans = max(ans, (i-nums[j])*ma[j+1]);
        }
        return ans>0?ans:0;
    }
};
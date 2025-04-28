class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        vector<long long> pref(n+1);
        pref[0] = 0;
        for(int i=0;i<n;i++) pref[i+1]=pref[i]+(long long)nums[i];

        int r =0;
        long long ans=0;
        for(int l=0;l<n;l++){
            while(r<n && (pref[r+1]-pref[l])*(r+1-l)<k){
                r++;
            }
            ans+=r-l;

        }
    return ans;
    }
};
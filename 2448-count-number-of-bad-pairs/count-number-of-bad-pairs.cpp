class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        unordered_map<int,int> s_l; //good sequence index (i-num[i])and occurance
        int n = nums.size();
        long long gp =0;
        for(int i =0; i<n; i++){
            s_l[nums[i]-i]++;
        }
        for(const auto& [s, l] : s_l){
            if(l==1) continue;
            gp+=(long long)l*(l-1)/2;
        }
        return (long long)n*(n-1)/2-gp;
    }
};
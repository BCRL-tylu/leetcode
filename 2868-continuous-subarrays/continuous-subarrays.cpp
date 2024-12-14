class Solution {
public:
    static long long continuousSubarrays(vector<int>& nums) {
        const int n=nums.size();
        long long cnt=0;
        map<int, int> hasX;
        for(int l=0, r=0; r<n; r++){
            hasX[nums[r]]++;
            while(l<r && prev(hasX.end())->first-hasX.begin()->first>2){
                int f=--hasX[nums[l]];
                if (f==0) hasX.erase(nums[l]);
                l++;
            }
            cnt+=r-l+1LL;
        }
        return cnt;
    }
};

auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
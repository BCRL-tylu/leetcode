class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        int lk = INT_MAX, n = nums.size();
        vector<int> ans;
        vector<pair<int,int>> coordi;
        for (int i = 0; i < n; i++) {
            if (nums[i] == key) {
                coordi.push_back({max(0,i-k),min(n-1,i+k)});
            }
        }
        int r = -1;
        for(auto [f,s]:coordi){
            for(int l=max(f,r);l<=s;l++){
                ans.push_back(l);
            }
            r = max(r,s+1);
        }

        return ans;
    }
};
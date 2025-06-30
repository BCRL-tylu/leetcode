class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> freq;
        vector<int> uni;
        for (auto k : nums) {
            freq[k]++;
        }
        for (auto [l, r] : freq) {
            uni.push_back(l);
        }
        sort(uni.begin(),uni.end());
        int ans = 0;
        for (auto k:uni) {
            if (freq[k+1] != 0 && freq[k]!=0) {
                ans = max(freq[k] + freq[k+1], ans);
            }
        }
        return ans;
    }
};
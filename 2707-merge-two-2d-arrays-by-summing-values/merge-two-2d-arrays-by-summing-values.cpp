class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        unordered_map<int,int> ans;
        vector<vector<int>> rt;
        for(int i =0;i<(int)nums1.size();i++){
            ans[nums1[i][0]] = nums1[i][1];
        }
        
        for(int i =0;i<(int)nums2.size();i++){
            ans[nums2[i][0]] += nums2[i][1];
        }

        for(auto p:ans){
            rt.push_back({p.first,p.second});
        }
        sort(rt.begin(),rt.end());
        return rt;
    }
};
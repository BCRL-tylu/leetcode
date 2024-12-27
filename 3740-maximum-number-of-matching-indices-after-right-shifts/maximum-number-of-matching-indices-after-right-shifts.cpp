class Solution {
public:
    int maximumMatchingIndices(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        unordered_map<int, vector<int>> hm;
        // Step 1: Build the hashmap for nums2
        for (int i = 0; i < n; ++i) {
            hm[nums2[i]].emplace_back(i);
        }
        // Step 2: Calculate the right shift distances and track the maximum matches
        vector<int> distance_vector(n, 0);
        int max_matches = 0;
        for (int i = 0; i < n; ++i) {
            if (hm.count(nums1[i])) {
                for (int idx : hm[nums1[i]]) {
                    max_matches = max(max_matches, ++distance_vector[(idx-i+n) % n]);// Right shift distance
                }
            }
        }
        return max_matches;
    }
};

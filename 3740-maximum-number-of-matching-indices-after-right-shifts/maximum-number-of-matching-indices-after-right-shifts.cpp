class Solution {
public:
    int maximumMatchingIndices(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        unordered_map<int, vector<int>> hm;

        // Step 1: Build the hashmap for nums2
        for (int i = 0; i < n; ++i) {
            hm[nums2[i]].emplace_back(i);
        }
        // Step 2: Precompute the modulo results for all possible differences
        vector<int> precomputedModulo(2 * n);
        for (int diff = -n; diff < n; ++diff) {
            precomputedModulo[diff + n] = (diff + n) % n;
        }
        // Step 3: Calculate the right shift distances and track the maximum matches
        vector<int> distance_vector(n, 0);
        int max_matches = 0;
        for (int i = 0; i < n; ++i) {
            if (hm.count(nums1[i])) {
                for (int idx : hm[nums1[i]]) {
                    max_matches = max(max_matches, ++distance_vector[precomputedModulo[idx - i + n]]);
                }
            }
        }
        return max_matches;
    }
};

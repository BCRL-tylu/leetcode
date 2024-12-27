class Solution {
public:
    int maximumMatchingIndices(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        unordered_map<int, vector<int>> indexMap;

        // Step 1: Build the hashmap for nums2 with indices
        for (int i = 0; i < n; ++i) {
            indexMap[nums2[i]].push_back(i);
        }

        // Step 2: Initialize the distance vector
        vector<int> distance_vector(n, 0);
        int max_matches = 0;

        // Step 3: Calculate the right shift distances and track the maximum matches
        for (int i = 0; i < n; ++i) {
            int num = nums1[i];
            if (indexMap.count(num)) {
                for (int idx : indexMap[num]) {
                    int distance = (idx - i + n) % n; // Right shift distance
                    distance_vector[distance]++;
                    max_matches = max(max_matches, distance_vector[distance]);
                }
            }
        }
        return max_matches;
    }
};

class Solution {
public:
    int maximumMatchingIndices(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        unordered_map<int, vector<int>> hm;

        // Step 1: Build the hashmap for nums2
        for (int i = 0; i < n; ++i) {
            hm[nums2[i]].push_back(i);
        }

        // Step 2: Initialize the distance vector
        vector<int> distance_vector(n, 0);
        int m = 0;
        // Step 3: Calculate the right shift distances
        for (int i = 0; i < n; ++i) {
            if (hm.count(nums1[i])) {
                for (int idx : hm[nums1[i]]) {
                    int distance = (idx - i + n) % n; // Right shift distance
                    m = max(m,++distance_vector[distance]);
                }
            }
        }
        // Step 4: Return the maximum value in distance vector
        return m;
    }
};

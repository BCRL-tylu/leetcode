class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<long long> ans(n, 0);
        vector<pair<int, int>> n1(n);
        for (int i = 0; i < n; i++) {
            n1[i] = {nums1[i], i};
        }
        sort(n1.begin(), n1.end());
        
        // Use a set of long long to store the elements from nums2.
        multiset<long long> heap;
        long long k_largest = 0;
        
        for (int i = 0; i < n; i++) { // Process from smaller to larger nums1 values.
            long long pre_k_larg = k_largest;
            while (i + 1 < n && n1[i].first == n1[i + 1].first) {
                int index = n1[i].second;
                heap.insert(nums2[index]);
                k_largest += nums2[index];
                
                // If the heap size exceeds k, remove the smallest element.
                if (heap.size() > k) {
                    k_largest -= *heap.begin();
                    heap.erase(heap.begin());
                }
                ans[index] = pre_k_larg;
                i++;
            }
            if (i != n) { // Process the last element of the current group.
                int index = n1[i].second;
                heap.insert(nums2[index]);
                k_largest += nums2[index];
                if (heap.size() > k) {
                    k_largest -= *heap.begin();
                    heap.erase(heap.begin());
                }
                ans[index] = pre_k_larg;
            }
        }
        return ans;
    }
};
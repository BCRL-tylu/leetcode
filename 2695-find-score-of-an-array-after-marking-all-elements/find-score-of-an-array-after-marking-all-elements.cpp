class Solution {
public:
    std::unordered_map<int, int> storeOrderAndIndex(const std::vector<int>& v) {
        std::vector<std::pair<int, int>> valueIndexPairs;
        for (int i = 0; i < v.size(); ++i) {
            valueIndexPairs.emplace_back(v[i], i);
        }
        std::sort(valueIndexPairs.begin(), valueIndexPairs.end());
        std::unordered_map<int, int> orderIndexMap;

        for (int i = 0; i < valueIndexPairs.size(); ++i) {
            orderIndexMap[i] = valueIndexPairs[i].second;
        }
        return orderIndexMap;
    }

    long long findScore(vector<int>& nums) {
        unordered_map<int, int> hm = storeOrderAndIndex(nums);
        unordered_map<int, int> hashmap;
        int n = nums.size();
        for (size_t i = 0; i < n; ++i) {
            hashmap[i] = nums[i];
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int ind = hashmap[hm[i]];
            if (ind != -1) {
                ans += ind;
                hashmap[hm[i] - 1] = -1;
                hashmap[hm[i] + 1] = -1;
            }
        }
        return ans;
    }
};
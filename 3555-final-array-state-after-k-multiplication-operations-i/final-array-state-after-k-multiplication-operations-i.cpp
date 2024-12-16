class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        std::set<std::pair<int, int>> orderedPairs;
    int n = nums.size();
    // Populate the set
    for (int i = 0; i < n; ++i) {
        orderedPairs.insert({nums[i], i});
    }

    for (int i =0;i<k;i++){
        auto temppair = orderedPairs.begin();
        pair<int, int> holder = {(temppair->first)*multiplier,temppair->second};
        orderedPairs.erase(temppair);
        orderedPairs.emplace(holder);
    }

    vector<int> rt(n);

    for(const auto& pair : orderedPairs){
        rt[pair.second] = pair.first;
    }
    return rt;

    }
};
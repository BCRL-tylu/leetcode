class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> orderedPairs;
    int n = nums.size();
    // Populate the set
    for (int i = 0; i < n; ++i) {
        orderedPairs.push({nums[i], i});
    }

    for (int i =0;i<k;i++){
        auto temppair = orderedPairs.top();
        orderedPairs.pop();
        orderedPairs.push({(temppair.first)*multiplier,temppair.second});
    }

    vector<int> rt(n);

    for(int i = 0; i < n; ++i){
        auto temppair = orderedPairs.top();
        orderedPairs.pop();
        rt[temppair.second] = temppair.first;
    }
    return rt;
    }
};
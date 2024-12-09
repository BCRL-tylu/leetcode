class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums,
                                vector<vector<int>>& queries) {
        int n = nums.size();
        std::vector<bool> rt(n - 1, true);
        std::vector<bool> r;
        for (int i = 0; i < nums.size() - 1; i++) {
            if (!((nums[i + 1] - nums[i]) % 2)) {
                rt[i] = false;
            }
        }
         std::unordered_map<int, int> skip;
        for (int k = 0; k < queries.size(); k++) {
            bool result = true; // Identity element for AND
            for (int m = queries[k][0]; m < queries[k][1]; m++) {
                if(skip[m] == 0){
                    result &= rt[m];
                }else{
                    result &= rt[m];
                    m = max(skip[m],m);
                }
                if (!result){
                    break; // Optimization: stop early if result is false
                }
            }
            if(result){
                skip[queries[k][0]] = max(queries[k][1]-1,skip[queries[k][0]]);
            }
            r.push_back(result);
        }
        return r;
    }
};
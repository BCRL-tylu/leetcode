class Solution {
public:
    //******nvdpsaluja******

    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {
        int n = original.size();
        int left = bounds[0][0], right = bounds[0][1];
        for (int i = 1; i < n; i++) {
            int diff = (original[i] - original[0]);
            left = max(left, bounds[i][0] - diff); 
            right = min(right, bounds[i][1] - diff);
        }
        return max(0, right - left + 1);
    }
};
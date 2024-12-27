class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int maxRight = values.back() - (values.size() - 1);
        int maxScore = INT_MIN;
        for (int i = values.size() - 2; i >= 0; --i) {
            maxScore = max(maxScore, values[i] + i + maxRight);
            maxRight = max(maxRight, values[i] - i);
        }
        return maxScore;
    }
};

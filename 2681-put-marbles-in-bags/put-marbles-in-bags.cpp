#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int n = weights.size();
        if (k == 1) return 0;
        long long base = (long long)weights.front() + weights.back();
        vector<long long> contributions;
        for (int i = 0; i < n - 1; i++)  contributions.push_back(weights[i] + weights[i+1]);
        // Sort contributions so that we can choose the smallest for the minimal score
        // and the largest for the maximum score.
        sort(contributions.begin(), contributions.end());

        long long minScore = base, maxScore = base;
        // For minimal score, add the (k-1) smallest contributions.
        for (int i = 0; i < k - 1; i++) {
            minScore += contributions[i];
            maxScore += contributions[contributions.size() - 1 - i];
        }
        return maxScore - minScore;
    }
};

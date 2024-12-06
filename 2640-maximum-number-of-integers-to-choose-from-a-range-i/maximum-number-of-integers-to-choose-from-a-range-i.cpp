class Solution {
public:
    int maxCount(std::vector<int>& banned, int n, int maxSum) {
        std::unordered_set<int> bannedSet(banned.begin(), banned.end());
        int sum = 0, count = 0;

        for (int i = 1; i <= n; ++i) {
            if (bannedSet.count(i)) {
                continue; // Skip banned numbers
            }
            if(i>maxSum){
                break;
            }
            if (sum + i > maxSum) {
                break; // Stop if adding `i` exceeds `maxSum`
            }
            sum += i;
            ++count;
        }
        return count;
    }
};

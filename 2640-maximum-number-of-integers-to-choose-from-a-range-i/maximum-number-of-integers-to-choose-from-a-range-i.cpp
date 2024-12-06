class Solution {
public:
    int maxCount(std::vector<int>& banned, int n, int maxSum) {
        std::vector<bool> isBanned(n + 1, false);

        // Mark banned numbers using a bit array
        for (int num : banned) {
            if (num <= n) {
                isBanned[num] = true;
            }
        }

        int sum = 0, count = 0;

        // Iterate through numbers from 1 to n
        for (int i = 1; i <= n; ++i) {
            if (isBanned[i]) {
                continue; // Skip banned numbers
            }
            if (i>maxSum||sum + i > maxSum) {
                break; // Stop if adding `i` exceeds `maxSum`
            }
            sum += i;
            ++count;
        }

        return count;
    }
};

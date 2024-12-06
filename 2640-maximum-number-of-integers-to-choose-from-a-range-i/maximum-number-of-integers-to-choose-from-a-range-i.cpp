class Solution {
public:
    int maxCount(std::vector<int>& banned, int n, int maxSum) {
        std::vector<bool> isBanned(n + 1, false);
        for (int num : banned) {
            if (num <= n)
                isBanned[num] = true;
        }

        int sum = 0;
        short count = 0;

        for (int i = 1; i <= n; ++i) {
            if (isBanned[i]) continue;
            if (sum + i > maxSum) break;
            sum += i;
            ++count;
        }
        return count;
    }
};

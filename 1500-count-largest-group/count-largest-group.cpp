class Solution {
public:
    int digitSum(int n) {
        int ans = 0;

        while (n) {
            ans += n % 10;
            n /= 10;
        }

        return ans;
    }

    int countLargestGroup(int n) {
        unordered_map<int, int> freq;
        int maxi = 0;

        for (int i = 1; i <= n; i++) {
            int sum = digitSum(i);
            freq[sum]++;

            if (freq[sum] > maxi) {
                maxi = freq[sum];
            }
        }

        int ans = 0;

        for (auto& [_, fr] : freq) {
            if (fr == maxi) {
                ans++;
            }
        }

        return ans;
    }
};
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maximumSum(vector<int>& nums) {
        vector<pair<int, int>> hm(82, {INT_MIN, INT_MIN}); // Using fixed-size vector instead of hashmap
        int ans = -1;

        for (int num : nums) {
            int k = num;  // Store original number before modifying num
            int ind = 0;

            while (num) {
                ind += num % 10;
                num /= 10;
            }

            auto& [f, s] = hm[ind];

            if (k > f) {
                s = f;
                f = k;
            } else if (k > s) {
                s = k;
            }
                ans = max(ans, f + s);
        }
        return ans;
    }
};

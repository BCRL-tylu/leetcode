#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    int sumdigit(int k) {
        int r = 0;
        while (k) {
            r += k % 10;
            k /= 10;
        }
        return r;
    }

public:
    int maximumSum(vector<int>& nums) {
        vector<pair<int, int>> hm(82, {0, 0});  // Using fixed-size vector instead of hashmap
        int ans = -1;

        for (int num : nums) {
            int ind = sumdigit(num);
            auto& [first, second] = hm[ind];

            if (num > first) {
                second = first;
                first = num;
            } else if (num > second) {
                second = num;
            }
            if (second > 0) {  // Ensure two valid numbers exist
                ans = max(ans, first + second);
            }
        }
        return ans;
    }
};

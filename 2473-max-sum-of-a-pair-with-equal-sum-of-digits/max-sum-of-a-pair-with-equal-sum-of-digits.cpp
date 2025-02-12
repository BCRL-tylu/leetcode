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
            auto& [f, s] = hm[ind];
            if (num > f) {
                s = f;
                f = num;
            } else if (num > s) {
                s = num;
            } else{
                continue;
            }
            if (s > 0) {  // Ensure two valid numbers exist
                ans = max(ans, f + s);
            }
        }
        return ans;
    }
};

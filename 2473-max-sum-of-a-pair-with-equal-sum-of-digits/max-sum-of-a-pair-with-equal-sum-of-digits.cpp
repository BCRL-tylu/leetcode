#include <iostream>
#include <vector>
#include <unordered_map>
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
        unordered_map<int, pair<int, int>> hm;
        int ans = -1;

        for (int num : nums) {
            int ind = sumdigit(num);
            auto& [first, second] = hm[ind];  // Reference to avoid extra copies

            if (num > first) {
                second = first;
                first = num;
            } else if (num > second) {
                second = num;
            }

            if (second != 0) {  // Ensure we have at least two numbers
                ans = max(ans, first + second);
            }
        }
        return ans;
    }
};

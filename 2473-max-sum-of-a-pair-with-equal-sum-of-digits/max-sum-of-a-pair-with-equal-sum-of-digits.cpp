#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class tt {
    int first = INT_MIN, second = INT_MIN;
public:
    void insert(int x) {
        if (x > first) {
            second = first;
            first = x;
        } else if (x > second) {
            second = x;
        }
    }
    int gsum() const {
        return first + second;
    }
};

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
        unordered_map<int, tt> hm;
        int ans = -1;

        for (int num : nums) {
            int ind = sumdigit(num);
            hm[ind].insert(num);
            ans = max(ans, hm[ind].gsum());
        }

        return ans;
    }
};

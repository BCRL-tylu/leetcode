#include <vector>
using namespace std;

class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> result(k, 0);
        vector<long long> prevCount(k, 0), currCount(k, 0);
        for (int i = 0; i < n; i++) {
            int v = nums[i] % k;
            if (v < 0) v += k;
            for (int r = 0; r < k; r++) 
                currCount[r] = 0;
            currCount[v] = 1;
            for (int r = 0; r < k; r++) {
                currCount[(r * v) % k] += prevCount[r];
            }

            for (int r = 0; r < k; r++) {
                result[r] += currCount[r];
            }
            prevCount.swap(currCount);
        }
        return result;
    }
};

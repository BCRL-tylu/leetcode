int b = 82;

class tt {
    int first = INT_MIN, second = INT_MIN;  // Use LLONG_MIN to handle negatives
public:
    void insert(int x) {
        if (x > first) {
            second = first;  // Move first to second
            first = x;
        } else if (x > second) {
            second = x;  // Update second if it's in between
        }
    }
    int gsum() const{
        return first+second;
    }
};
class Solution {
private:
    int sumdigit(int k) {
        int r = 0;
        while (k != 0) {
            r += k % 10;
            k /= 10;
        }
        return r;
    }

public:
    int maximumSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> sd,digsum(b,-1); // sum of digits
        unordered_map<int,tt>hm;
        int ans = -1;
        for (int i = 0; i < n; i++) {
            int ind = sumdigit(nums[i]);
            hm[ind].insert(nums[i]);
            digsum[ind] = max(digsum[ind],hm[ind].gsum());
            ans = max(ans,digsum[ind]);
        }
        return ans;
    }
};
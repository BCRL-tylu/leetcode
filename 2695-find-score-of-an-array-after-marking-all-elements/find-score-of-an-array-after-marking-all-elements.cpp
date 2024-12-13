std::vector<bool> marked(1e5 + 1, true);
class Solution {
public:
    long long findScore(vector<int> &nums) {
        long long ans = 0;
        for (int i = 0, n = nums.size(); i < n; i += 2) { // i 选了 i+1 不能选
            int i0 = i;
            while (i + 1 < n && nums[i] > nums[i + 1]) // 找到下坡的坡底
                ++i;
            for (int j = i; j >= i0; j -= 2) // 从坡底 i 到坡顶 i0，每隔一个累加
                ans += nums[j];
        }
        return ans;
    }
};
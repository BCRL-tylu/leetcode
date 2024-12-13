class Solution {
public:
    long long findScore(vector<int>& nums) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        int n = nums.size();
        // Fill the min-heap with values and their indices
        for (int i = 0; i < n; ++i) {
            pq.emplace(nums[i], i);
        }
        std::vector<bool> marked(n+1, true);

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            auto pair = pq.top();
            pq.pop();
            int temp = pair.second;
            if (marked[temp]) {
                ans += pair.first;
                marked[max(temp - 1,0)] = false;
                marked[temp + 1] = false;
            }
        }
        return ans;
    }
};
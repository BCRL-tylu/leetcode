class Solution {
public:
    struct SegmentTree {
        struct Node {
            long long totalSum, maxSubarraySum, maxPrefixSum, maxSuffixSum;
            Node() : totalSum(0), maxSubarraySum(LLONG_MIN), maxPrefixSum(LLONG_MIN), maxSuffixSum(LLONG_MIN) {}
            Node(long long val) : totalSum(val), maxSubarraySum(val), maxPrefixSum(val), maxSuffixSum(val) {}
        };

        int n;
        vector<Node> tree;

        SegmentTree(const vector<int>& nums) {
            n = nums.size();
            tree.resize(4 * n);
            build(nums, 0, 0, n - 1);
        }

        void build(const vector<int>& nums, int node, int start, int end) {
            if (start == end) {
                tree[node] = Node(nums[start]);
                return;
            }
            int mid = (start + end) / 2;
            build(nums, 2 * node + 1, start, mid);
            build(nums, 2 * node + 2, mid + 1, end);
            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
        }

        Node merge(const Node& left, const Node& right) {
            Node result;
            result.totalSum = left.totalSum + right.totalSum;
            result.maxPrefixSum = max(left.maxPrefixSum, left.totalSum + right.maxPrefixSum);
            result.maxSuffixSum = max(right.maxSuffixSum, right.totalSum + left.maxSuffixSum);
            result.maxSubarraySum = max({left.maxSubarraySum, right.maxSubarraySum, left.maxSuffixSum + right.maxPrefixSum});
            return result;
        }

        void update(int idx, int value, int node, int start, int end) {
            if (start == end) {
                tree[node] = Node(value);
                return;
            }
            int mid = (start + end) / 2;
            if (idx <= mid) update(idx, value, 2 * node + 1, start, mid);
            else update(idx, value, 2 * node + 2, mid + 1, end);
            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
        }

        Node query() {
            return tree[0];
        }
    };

    long long maxSubarraySum(vector<int>& nums) {
        // Check if all numbers are negative
        long long maxElement = LLONG_MIN;
        bool allNegative = true;
        for (int num : nums) {
            if (num > 0) {
                allNegative = false;
            }
            maxElement = max(maxElement, (long long)num);
        }

        // If all elements are negative, the result is the largest single element
        if (allNegative) {
            return maxElement;
        }

        unordered_map<int, vector<int>> freq;
        for (int i = 0; i < nums.size(); ++i) {
            freq[nums[i]].push_back(i);
        }

        SegmentTree segTree(nums);
        long long result = segTree.query().maxSubarraySum;

        for (auto& [key, indices] : freq) {
            for (int idx : indices) {
                segTree.update(idx, 0, 0, 0, nums.size() - 1);
            }
            result = max(result, segTree.query().maxSubarraySum);
            for (int idx : indices) {
                segTree.update(idx, nums[idx], 0, 0, nums.size() - 1);
            }
        }

        return result;
    }
};

struct node {
    long long lsum, rsum, sum, m;
};

struct segmentTree {
vector<node> tree;

public:
   segmentTree(int n) : tree(vector<node>(n << 2)) {}
    
    long long query(int ind, int left, int right, int x, int y) {
        if (left >= x && right <= y) {
            return tree[ind].m;
        }
        const int mid = (left + right) >> 1;
        long long r = LONG_LONG_MIN;
        if (x <= mid) {
            r = query(ind << 1, left, mid, x, y);
        }
        if (y > mid) {
            r = max(r, query((ind << 1) | 1, mid + 1, right, x, y));
        } 
        return r;
    }

    void update(int ind, int left, int right, int x, int delta) {
        if (left >= x && right <= x) {
            tree[ind].lsum += delta;
            tree[ind].rsum += delta;
            tree[ind].sum += delta;
            tree[ind].m += delta;
            return;
        }
        const int mid = (left + right) >> 1, lson = ind << 1, rson = (ind << 1) | 1;
        if (x <= mid) {
            update(lson, left, mid, x, delta);
        } else {
            update(rson, mid + 1, right, x, delta);
        }
        tree[ind].lsum = max(tree[lson].lsum, tree[lson].sum + tree[rson].lsum);
        tree[ind].rsum = max(tree[rson].rsum, tree[rson].sum + tree[lson].rsum);
        tree[ind].sum = tree[lson].sum + tree[rson].sum;
        tree[ind].m = max(max(tree[lson].m, tree[rson].m), tree[lson].rsum + tree[rson].lsum);
    }
};

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums) {
        const int n = nums.size();
        segmentTree t(n);
        unordered_map<int, vector<int>> have;
        for (int i = 0; i < n; ++i) {
            t.update(1, 0, n - 1, i, nums[i]);
            if (nums[i] < 0) {
                have[nums[i]].push_back(i);
            }
        }
        long long r = t.query(1, 0, n - 1, 0, n - 1);
        if (r <= 0) return r;
        for (const auto& p : have) {
            for (int i : p.second) {
                t.update(1, 0, n - 1, i, -p.first);
            }
            r = max(r, t.query(1, 0, n - 1, 0, n - 1));
            for (int i : p.second) {
                t.update(1, 0, n - 1, i, p.first);
            }
        }
        return r;
    }
};
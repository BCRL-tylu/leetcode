class SegmentTreeMax {
public:
    int n;
    vector<long long> tree;
    
    SegmentTreeMax(const vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, n - 1, 0);
    }
    
    void build(const vector<long long>& arr, int l, int r, int idx) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(arr, l, mid, 2 * idx + 1);
        build(arr, mid + 1, r, 2 * idx + 2);
        tree[idx] = max(tree[2 * idx + 1], tree[2 * idx + 2]);
    }
    
    long long query(int ql, int qr, int l, int r, int idx) {
        if (ql <= l && r <= qr) return tree[idx];
        if (r < ql || l > qr) return LLONG_MIN;
        int mid = l + (r - l) / 2;
        long long left = query(ql, qr, l, mid, 2 * idx + 1);
        long long right = query(ql, qr, mid + 1, r, 2 * idx + 2);
        return max(left, right);
    }
    
    long long query(int l, int r) {
        return query(l, r, 0, n - 1, 0);
    }
};

class SegmentTreeMin {
public:
    int n;
    vector<long long> tree;
    
    SegmentTreeMin(const vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, n - 1, 0);
    }
    
    void build(const vector<long long>& arr, int l, int r, int idx) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(arr, l, mid, 2 * idx + 1);
        build(arr, mid + 1, r, 2 * idx + 2);
        tree[idx] = min(tree[2 * idx + 1], tree[2 * idx + 2]);
    }
    
    long long query(int ql, int qr, int l, int r, int idx) {
        if (ql <= l && r <= qr) return tree[idx];
        if (r < ql || l > qr) return LLONG_MAX;
        int mid = l + (r - l) / 2;
        long long left = query(ql, qr, l, mid, 2 * idx + 1);
        long long right = query(ql, qr, mid + 1, r, 2 * idx + 2);
        return min(left, right);
    }
    
    long long query(int l, int r) {
        return query(l, r, 0, n - 1, 0);
    }
};

class Solution {
public:
    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {
        int n = original.size();
        vector<long long> L(n), R(n);
        
        // Compute offset: copy[i] = x + (original[i] - original[0])
        for (int i = 0; i < n; i++) {
            long long offset = (long long)original[i] - original[0];
            L[i] = (long long)bounds[i][0] - offset;
            R[i] = (long long)bounds[i][1] - offset;
        }
        
        // Build segment trees for range maximum over L and range minimum over R
        SegmentTreeMax segMax(L);
        SegmentTreeMin segMin(R);
        
        long long maxL = segMax.query(0, n - 1);
        long long minR = segMin.query(0, n - 1);
        
        if (maxL > minR) return 0;
        // The number of valid starting values x is (minR - maxL + 1)
        return (int)(minR - maxL + 1);
    }
};

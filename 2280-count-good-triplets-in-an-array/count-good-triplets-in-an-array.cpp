class BIT {
public:
    vector<int> tree;
    int n;
    
    BIT(int n): n(n) {
        tree.resize(n + 1, 0);
    }
    void update(int idx, int val) {
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
};

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> pos2(n);
        
        for (int i = 0; i < n; i++) {
            pos2[nums2[i]] = i;
        }
        
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = pos2[nums1[i]];
        }

        vector<long long> leftCount(n, 0);
        BIT bitLeft(n); 
        for (int i = 0; i < n; i++) {
            leftCount[i] = bitLeft.query(arr[i] + 1);  
            bitLeft.update(arr[i] + 1, 1);
        }
        
        vector<long long> rightCount(n, 0);
        BIT bitRight(n);
        for (int i = n - 1; i >= 0; i--) {
            int total = bitRight.query(n);
            int lessOrEqual = bitRight.query(arr[i] + 1);
            rightCount[i] = total - lessOrEqual;
            bitRight.update(arr[i] + 1, 1);
        }
        
        long long answer = 0;
        for (int i = 0; i < n; i++) {
            answer += leftCount[i] * rightCount[i];
        }
        
        return answer;
    }
};

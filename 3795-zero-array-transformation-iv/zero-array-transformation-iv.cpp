class Solution {
public:
    int minZeroArray(vector<int>& a, vector<vector<int>>& q) {
        int m = q.size(), n = a.size();
        int L = 0, R = m, ans = -1;
        while(L <= R){
            int mid = L + (R - L) / 2;
            if(check(mid, a, q)){
                ans = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        return ans;
    }
private:
    bool check(int k, vector<int>& a, vector<vector<int>>& q){
        int n = a.size();
        for(int i = 0; i < n; i++){
            bitset<1001> dp;
            dp.reset();
            dp[0] = 1;
            for(int j = 0; j < k; j++){
                if(q[j][0] <= i && i <= q[j][1])
                    dp |= (dp << q[j][2]);
            }
            if(!dp.test(a[i])) return false;
        }
        return true;
    }
};
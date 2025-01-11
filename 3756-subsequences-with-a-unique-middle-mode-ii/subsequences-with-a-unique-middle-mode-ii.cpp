class Solution {
    const int M = 1000000007, RM = (M + 1) / 2;
    
    int mul(long long x, long long y) {
        return x * y % M;
    }
    
    int sqr(int x) {
        return mul(x, x);
    }
    
    int add(int x, int y) {
        if ((x += y) >= M) {
            x -= M;
        }
        return x;
    } 
    
    int sub(int x, int y) {
        if ((x -= y) < 0) {
            x += M;
        }
        return x;
    }
    
    int C2(int n) {
        return mul(mul(n, n - 1), RM);
    }
    
    int count(const vector<int> &v, const vector<int> &c, bool countIfEqual) {
        const int n = v.size(), m = c.size();
        vector<int> t(m);
        int r = 0, R2 = 0;
        for (int i = 0; i < m; ++i) {
            R2 = add(R2, sqr(c[i]));
        }
        int RT = 0, R2T = 0;
        for (int i = 0; i < n; ++i) {
            const int x = v[i];
            int rx = c[x] - t[x];
            //left = 1, right = 0
            const int r2 = sub(R2, sqr(rx)), rt = sub(RT, mul(rx, t[x])), r2t = sub(R2T, mul(sqr(rx), t[x])), p = n - i - rx, sumt = i - t[x];
            // Sigma((right_no_x - right[j]) ^ 2) - (r2_no_x - right[j] ^ 2) * t[j] * t[x] / 2
            // t[x] / 2 can be done finally
            // P = n - i - right[x]
            //((P - right[j]) ^ 2 - right2 + right[x] ^ 2 + right[j] ^ 2) * t[j]
            // (P ^ 2 - 2 * P * right[j] + 2 * right[j] ^ 2 +  - r2_no_x) * t[j]
            int temp = mul(sub(sqr(p), r2), sumt);
            temp = sub(temp, mul(mul(2, p), rt));
            temp = add(temp, mul(2, r2t));
            temp = mul(temp, mul(t[x], RM));
            r = add(r, temp);
            //left = 2, right = 0
            r = add(r, mul(C2(t[x]), C2(p)));
            //left = 2, right = 1
            --rx;
            r = add(r, mul(C2(t[x]), mul(rx, p)));
            if (countIfEqual) {
                // left = right = 1
                r = add(r, mul(mul(t[x], sumt), mul(rx, p)));
                // left = right = 2
                r = add(r, mul(C2(t[x]), C2(rx)));
            }  
            ++t[x];
            R2 = add(r2, sqr(rx));
            RT = add(rt, mul(rx, t[x]));
            R2T = add(r2t, mul(sqr(rx), t[x]));
        }
        return r;
        
    }
    
public:
    int subsequencesWithMiddleMode(vector<int>& nums) {
        unordered_map<int, int> mp;
        int m = 0;
        for (int& x : nums) {
            if (!mp.count(x)) {
                mp[x] = m++;
            }
            x = mp[x];
        }
        vector<int> c(m);
        for (int x : nums) {
            ++c[x];
        }
        int r = count(nums, c, true);
        reverse(nums.begin(), nums.end());
        return add(r, count(nums, c, false));
    }
};
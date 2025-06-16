struct GcdST {
    int N, LOG;
    vector<vector<int>> st;
    vector<int> lg;
    GcdST(const vector<int>& a) {
        N = a.size();
        LOG = 32 - __builtin_clz(N);
        st.assign(LOG, vector<int>(N));
        lg.assign(N+1,0);
        // precompute logs
        for(int i=2;i<=N;i++)
            lg[i] = lg[i/2] + 1;
        // level 0 is just the array
        for(int i=0;i<N;i++)
            st[0][i] = a[i];
        // build
        for(int k=1;k<LOG;k++){
            int len = 1<<(k-1);
            for(int i=0;i+2*len<=N;i++){
                st[k][i] = gcd(st[k-1][i], st[k-1][i+len]);
            }
        }
    }
    // query gcd of a[l..r] inclusive in O(1)
    int query(int l, int r){
        int k = lg[r-l+1];
        return gcd(st[k][l], st[k][r-(1<<k)+1]);
    }
};

class Solution {
public:
    long long maxGCDScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> e2(n), odd(n);
        for(int i=0;i<n;i++){
            e2[i]  = __builtin_ctz(nums[i]);
            odd[i] = nums[i] >> e2[i];
        }
        // build sparse table on odd[]
        GcdST st(odd);

        long long ans = 0;
        // for each left endpoint
        for(int l = 0; l < n; ++l){
            array<int,31> freq = {};  // counts of e2 in window
            // extend to r
            for(int r = l; r < n; ++r){
                freq[e2[r]]++;
                // 1) get the odd–gcd in O(1)
                int g = st.query(l, r);

                // 2) find the minimal exponent and its count
                int me = 0;
                while(freq[me] == 0) me++;
                int cnt = freq[me];

                // 3) can bump that min–exponent by +1 iff cnt ≤ k
                int E = me + (cnt <= k ? 1 : 0);

                long long total_gcd = (long long)g << E;
                long long score     = total_gcd * (r - l + 1LL);
                ans = max(ans, score);
            }
        }
        return ans;
    }
};

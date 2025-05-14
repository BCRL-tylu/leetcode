class Solution {
public:
    static constexpr int K = 26;
    static constexpr long long MOD = 1000000007;
    
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        // 1) Build initial frequency vector
        vector<long long> cur(K, 0);
        for (char c : s) cur[c - 'a']++;
        
        // 2) Build adjacency matrix M: M[i][j]=1 iff there's an edge i→j
        vector<vector<long long>> M(K, vector<long long>(K, 0));
        for (int i = 0; i < K; i++) {
            for (int step = 1; step <= nums[i]; step++) {
                int j = (i + step) % K;
                M[i][j] = 1;
            }
        }
        
        // 3) Repeated‐squaring loop: for each bit of t
        long long e = t;
        while (e > 0) {
            if (e & 1) {
                // cur = cur × M
                vector<long long> nxt(K, 0);
                for (int i = 0; i < K; i++) if (cur[i]) {
                    long long v = cur[i];
                    for (int j = 0; j < K; j++) {
                        nxt[j] = (nxt[j] + v * M[i][j]) % MOD;
                    }
                }
                cur.swap(nxt);
            }
            
            // M = M × M  (square the adjacency)
            vector<vector<long long>> MM(K, vector<long long>(K, 0));
            for (int i = 0; i < K; i++) {
                for (int k = 0; k < K; k++) if (M[i][k]) {
                    long long v = M[i][k];
                    for (int j = 0; j < K; j++) {
                        MM[i][j] = (MM[i][j] + v * M[k][j]) % MOD;
                    }
                }
            }
            M.swap(MM);
            e >>= 1;
        }
        
        // 4) Sum up final counts
        long long ans = 0;
        for (auto &x : cur) ans = (ans + x) % MOD;
        return int(ans);
    }
};

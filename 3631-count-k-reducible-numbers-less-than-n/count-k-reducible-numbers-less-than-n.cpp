class Solution {
public:
    int countKReducibleNumbers(string s, int k) {
        const int mod = 1e9 + 7;
        int n = s.size();

        auto setBitsIn = [&](int v) -> int {
            int ans = 0;
            for(int bit = 0; bit < 32; bit++) {
                if((v >> bit) & 1)
                    ans++;
            }
            return ans;
        };

        // we can have at max 800 set bits
        // filter out the number of set bits we can have to reach 1 with atmax k operations
        set<int> canHaveSetBits;
        unordered_map<int, int> t;
        for(int i = 1; i <= n; i++) {
            t[i] = 1 + t[setBitsIn(i)];
            if(t[i] <= k)
                canHaveSetBits.insert(i);
        }

        int dp[801][2][801];
        memset(dp, -1, sizeof(dp));

        // limit our recursive calls on the max number of set bits we can achieve
        auto recur = [&](auto&& recur, int pos, bool tight, int setBits) -> int {
            if(pos == n)
                return !tight && canHaveSetBits.count(setBits);
            if(setBits > *canHaveSetBits.rbegin())
                return 0;

            if(dp[pos][tight][setBits] != -1)
                return dp[pos][tight][setBits];

            // add 0 here
            int ans = recur(recur, pos + 1, tight && (s[pos] == '0'), setBits);

            // add 1 here
            if(!tight || s[pos] == '1')
                ans = (1ll * ans + recur(recur, pos + 1, tight && (s[pos] == '1'), setBits + 1)) % mod;
            return dp[pos][tight][setBits] = ans;
        };

        
        return recur(recur, 0, true, 0);
    }
};
class Solution {
    using int128 = __int128;
    
    unordered_map<long long, int128> memo;

    long long encode(int odd, int even, int req) {
        return odd + even * 10LL + req * 100LL;
    }

    int128 cap;
    

    int128 dp(int odd, int even, int req) {
        if (odd == 0 && even == 0)
            return 1;
        long long key = encode(odd, even, req);
        if (memo.count(key))
            return memo[key];
        int128 ways = 0;
        if (req == 2) {
            if (odd > 0) {
                int128 sub = dp(odd - 1, even, 0);
                ways += odd * sub;
                if (ways > cap) ways = cap;
            }
            if (even > 0) {
                int128 sub = dp(odd, even - 1, 1);
                ways += even * sub;
                if (ways > cap) ways = cap;
            }
        } else if (req == 1) { // must pick an odd
            if (odd > 0) {
                int128 sub = dp(odd - 1, even, 0);
                ways = odd * sub;
                if (ways > cap) ways = cap;
            }
        } else { 
            if (even > 0) {
                int128 sub = dp(odd, even - 1, 1);
                ways = even * sub;
                if (ways > cap) ways = cap;
            }
        }
        memo[key] = ways;
        return ways;
    }
    
public:
    vector<int> permute(int n, long long k) {
        int oddCount = (n + 1) / 2;
        int evenCount = n / 2;
        cap = k + 1; // we cap all dp values at k+1
        
        int128 total = dp(oddCount, evenCount, 2);
        if (k > (long long) total) return {};  // fewer than k valid permutations
        
        vector<int> result;
        vector<int> avail(n);
        iota(avail.begin(), avail.end(), 1);  
        int req = 2;  
        
        while (!avail.empty()) {
            bool chosen = false;
            for (int i = 0; i < avail.size(); i++) {
                int candidate = avail[i];
                int candidateParity = candidate & 1; // odd if 1, even if 0
                if (req != 2 && candidateParity != req)
                    continue;
                
                int128 cnt = 0;
                if (candidateParity == 1) { 
                    cnt = dp(oddCount - 1, evenCount, 0);
                } else {  
                    cnt = dp(oddCount, evenCount - 1, 1);
                }
                if (cnt < k) {
                    k -= (long long) cnt; 
                } else {
                    result.push_back(candidate);
                    avail.erase(avail.begin() + i);
                    if (candidateParity == 1)
                        oddCount--;
                    else
                        evenCount--;
                    req = (candidateParity == 1 ? 0 : 1);
                    chosen = true;
                    break;
                }
            }
            if (!chosen)
                break;  // logically should not happen if k is valid.
        }
        return result;
    }
};

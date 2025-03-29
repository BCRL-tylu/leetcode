class Solution {
private:
    // Fast modular exponentiation.
    int mod_pow(int base, long long exp) {
        const int mod = 1e9+7;
        long long result = 1, b = base % mod;
        while(exp > 0) {
            if(exp & 1)
                result = (result * b) % mod;
            b = (b * b) % mod;
            exp >>= 1;
        }
        return (int) result;
    }
    
    // Precompute prime scores for numbers up to maxVal.
    vector<int> computePrimeScores(int maxVal) {
        vector<int> ps(maxVal + 1, 0);
        for (int i = 2; i <= maxVal; i++) {
            if(ps[i] == 0) { // i is prime
                for (int j = i; j <= maxVal; j += i)
                    ps[j]++;
            }
        }
        return ps;
    }
    
public:
    int maximumScore(vector<int>& nums, int k) {
        const int mod = 1e9+7;
        int n = nums.size();
        
        // Compute prime scores (note: given constraint nums[i] <= 1e5)
        int maxVal = *max_element(nums.begin(), nums.end());
        vector<int> primeScore = computePrimeScores(maxVal);
        
        // For each index i, we want to compute how many subarrays would choose nums[i].
        // We'll compute left and right boundaries using monotonic stacks.
        vector<long long> left(n), right(n);
        // left: count of choices for left boundary.
        // For left, an index i is blocked by the nearest j to its left with
        // primeScore[j] >= primeScore[i] (>= because tie means j wins).
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while(!st.empty() && primeScore[nums[st.top()]] < primeScore[nums[i]])
                st.pop();
            // if st.empty(), then left[i] = i+1; otherwise, left[i] = i - st.top()
            left[i] = st.empty() ? (i + 1LL) : (i - st.top());
            st.push(i);
        }
        while(!st.empty()) st.pop();
        
        // right: count of choices for right boundary.
        // For right, we need the first j to the right such that primeScore[nums[j]] > primeScore[nums[i]].
        for (int i = n - 1; i >= 0; i--) {
            while(!st.empty() && primeScore[nums[st.top()]] <= primeScore[nums[i]])
                st.pop();
            right[i] = st.empty() ? (n - i) : (st.top() - i);
            st.push(i);
        }
        vector<pair<int, long long>> candidates; // {nums[i], frequency}
        for (int i = 0; i < n; i++) {
            long long freq = left[i] * right[i];
            candidates.push_back({nums[i], freq});
        }
        
        sort(candidates.begin(), candidates.end(), [](auto &a, auto &b) {
            return a.first > b.first;
        });
        
        long long ans = 1;
        for(auto &p : candidates) {
            if(k <= 0) break;
            int x = p.first;
            long long cnt = p.second;
            long long times = min((long long)k, cnt);
            ans = (ans * mod_pow(x, times)) % mod;
            k -= times;
        }
        return (int)ans;
    }
};

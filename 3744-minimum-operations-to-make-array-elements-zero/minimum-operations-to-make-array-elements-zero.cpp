class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long totalResult = 0;
        const int MAX_K = 15;
        
        for (auto &q : queries) {
            int l = q[0], r = q[1];
            long long totalOps = 0;
            
            unsigned long long lowBound = 1; // 4^(k-1) for k=1
            for (int k = 1; k <= MAX_K; k++) {
                unsigned long long highBound = lowBound * 4 - 1; // 4^k - 1
                
                int L_int = max((long long)l, (long long)lowBound);
                int R_int = min((long long)r, (long long)highBound);
                if (L_int <= R_int) {
                    long long count = (long long)R_int - L_int + 1;
                    totalOps += count * k;
                }
                lowBound *= 4;
                if (lowBound > (unsigned long long)r) break;
            }
            long long operationsForQuery = (totalOps + 1) / 2; // ceil(totalOps/2)
            totalResult += operationsForQuery;
        }
        return totalResult;
    }
};

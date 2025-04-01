class Solution {
public:
    long long minEliminationTime(vector<int>& timeReq, int splitTime) {
        int n = timeReq.size();
        long long lo = *max_element(timeReq.begin(), timeReq.end());
        long long hi = lo + (long long)(n - 1) * splitTime;
        long long ans = hi;
        
        while(lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            double sum = 0.0;
            bool valid = true;
            for (int r : timeReq) {
                if (mid < r) { 
                    valid = false; 
                    break; 
                }
                long long allowed = (mid - r) / splitTime;
                sum += pow(2.0, - (double) allowed);
            }
            if (!valid || sum > 1.0 + 1e-12) { 
                lo = mid + 1;
            } else {
                ans = mid;
                hi = mid - 1;
            }
        }
        return ans;
    }
};

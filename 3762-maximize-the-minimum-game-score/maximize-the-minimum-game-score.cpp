#include <bits/stdc++.h>
using namespace std;
 
class Solution {
private:
// This function checks whether it is possible to guarantee gameScore[i] >= x for all i using at most m moves.
bool feasible(long long x, const vector<int>& points, int m) {
    int n = points.size();
    if(x == 0) return true; // even if some indices aren’t visited, score remains 0.
 
    vector<long long> R(n,0);
    for (int i = 0; i < n; i++) {
        R[i] = (x + points[i] - 1) / points[i];
    }
 
    long long cost = 0;
    if(n == 1) {
        long long d0 = max(0LL, R[0] - 1);
        cost = 1 + 2*d0;
        return (cost <= m);
    }
 
    long long D0 = max(0LL, R[0] - 1);
    cost = 1 + 2 * D0;
    vector<long long> D(n, 0);
    D[0] = D0;
    for (int i = 1; i <= n - 2; i++) {
        long long base = D[i-1] + 1;
        D[i] = max(0LL, R[i] - base);
        cost += (1 + 2 * D[i]);
    }
    long long prevBonus = D[n-2] + 1;
    long long optionA = 1 + 2 * max(0LL, R[n-1] - prevBonus);
    long long optionB = 2 * max(0LL, R[n-1] - D[n-2]);
    long long lastCost = min(optionA, optionB);
    cost += lastCost;
    return (cost <= m);
}
public:
    long long maxScore(vector<int>& points, int m) {
        int n = points.size();
        int minPoint = *min_element(points.begin(), points.end());
        long long lo = 0, hi = (long long)m * minPoint;
        long long ans = 0;
        while(lo <= hi){
            long long mid = lo + (hi - lo) / 2;
            if(feasible(mid, points, m)){
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};
 
/*
// Example test cases:
int main(){
    {
        vector<int> pts = {2,4};
        int m = 3;
        Solution sol;
        cout << sol.maxScore(pts, m) << "\n"; // Expected output: 4.
    }
    {
        vector<int> pts = {1,2,3};
        int m = 5;
        Solution sol;
        cout << sol.maxScore(pts, m) << "\n"; // Expected output: 2.
    }
    return 0;
}
*/

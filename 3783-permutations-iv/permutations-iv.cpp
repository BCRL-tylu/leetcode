//time complexity: O(n^2)
//space complexity: O(n^2)


vector<long long> fact(101, LLONG_MAX);
vector<int> remain(2);

class Solution {

    long long calcPerms(int odd, int even) {
        long long fromOdd = fact[odd];
        long long fromEven = fact[even];

        long long total = LLONG_MAX;
        if (log10(fromOdd) + log10(fromEven) <= 18)
            total = fromOdd * fromEven;

        return total;
    }

    //placeOdd == -1, can place anything here, (haven't started)
    // 0: even
    // 1: odd
//    void solve(vector<int> &ans, int n, long long k, int placeOdd, vector<vector<bool>> &chosen) {
    void solve(vector<int> &ans, int n, long long k, int placeOdd, vector<bool> &chosen) {
        if (remain[0] + remain[1] == 0)
            return;
        
        long long next;
        if (placeOdd == -1)
            next = calcPerms(remain[1], remain[0] - 1);
        else
            next = calcPerms(remain[1] - placeOdd, remain[0] - !placeOdd);
        
        for (int i = 1; i <= n; i++) {
            if (placeOdd == -1 || ((i&1) == placeOdd)) {
//                if (!chosen[i&1][i]) {
                if (!chosen[i]) {
                    if (k > next)
                        k -= next;
                    else {
                        remain[i&1]--;
                        ans.push_back(i);
//                        chosen[i&1][i] = true;
                        chosen[i] = true;
                        solve(ans, n, k, !(i&1), chosen);
                        break;
                    }
                }
            }
        }
    }

public:
    vector<int> permute(int n, long long k) {        
        vector<int> ans;

        //init fact
        fact[0] = 1;
        for (int i = 1; i <= 18; i++) fact[i] = i * fact[i-1];
        
        //left0=even, left1=odd
        remain[0] = (n)/2;
        remain[1] = (n+1)/2;

        //all even/odd numbers
        //vector<vector<bool>> chosen(2, vector(n+1, false));
        vector<bool> chosen(n+1, false);

        //odd = 1
        //even = -1
        int placeOdd = n % 2 ? 1 : -1;

        solve(ans, n, k, placeOdd, chosen) ;

        return ans;
    }
};
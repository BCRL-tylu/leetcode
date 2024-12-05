#include <array>       // For using std::array
#include <cstdint>     // For uint64_t
#include <string>      // For std::string
using namespace std;   // Use the standard namespace


// Define the solution class
class Solution {
public:
int dp[801][801][2] = {}, dp_ops[801] = { INT_MAX }, mod = 1000000007;
int dfs(int i, int b, const string &s, int k, bool lim) {
    if (i == s.size())
        return dp_ops[b] < k;
    if (dp[i][b][lim] == 0) {
        dp[i][b][lim] = 1 + dfs(i + 1, b, s, k, lim && s[i] == '0');        
        if (s[i] == '1' || !lim)
            dp[i][b][lim] = (dp[i][b][lim] + dfs(i + 1, b + 1, s, k, lim)) % mod;    
    }
    return dp[i][b][lim] - 1;
}
int countKReducibleNumbers(string s, int k) {
    for (unsigned int i = 2; i < 801; ++i)
        dp_ops[i] = 1 + dp_ops[popcount(i)];
    return dfs(0, 0, s, k, true) - (dp_ops[count(begin(s), end(s), '1')] < k);
}
};

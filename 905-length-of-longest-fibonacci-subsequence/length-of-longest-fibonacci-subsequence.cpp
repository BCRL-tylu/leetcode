class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        unordered_map<int, bool> found;
        for (int i = 0; i < (int)arr.size(); i++) {
            found[arr[i]] = true;
        }
        int ans =INT_MIN;
        vector<int> dp(1000);

        for (int i = 0; i < (int)arr.size() - 2; i++) {
            // Initialize the first two Fibonacci numbers
            dp[0] = arr[i];
            for (int j = i + 1; j < (int)arr.size() - 1; j++) {
                dp[1] = arr[j];
                int m = 2;
                while(true){
                    dp[m] = dp[m-1]+dp[m-2];
                    if(!found.count(dp[m]))break;
                    m++;
                }
                ans = max(ans,m);
            }
        }
        return ans==2?0:ans;
    }
};
class Solution {
public:

    int beautifulSplits(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> lcps(n, vector<int>(n, 0));
        // lcps[i][j] = length of the longest common prefix between nums[i:] and nums[j:]
        for (int x = 0 ; x < n ; ++x) {
            auto & lcp = lcps[x];
            int max_i = x, max_r = x;
            for (int i = x + 1 ; i < n ; ++i) {
                if (max_r >= i) {
                    lcp[i] = min(max_r - i + 1, lcp[i - max_i + x]);
                }
                while (i + lcp[i] < n && nums[i + lcp[i]] == nums[lcp[i] + x]) ++lcp[i];
                if (i + lcp[i] - 1 > max_r) {
                    max_i = i;
                    max_r = i + lcp[i] - 1;
                }
            }
        }


        int ans = 0;
        for (int i = 0 ; i < n ; ++i) {
            for (int j = i + 1 ; j < n - 1 ; ++j) {
                // split: [0,i], [i+1,j], [j+1,n-1]
                // check if prefix is satisfied

                if (lcps[0][i + 1] >= i + 1 && j - i >= i + 1 ) {
                    ++ans;
                    continue ;
                }
                if (lcps[i+1][j+1] >= j - i) {                
                    ++ans;
                    continue ;
                }
            }
        }

        return ans;
    }
};
class Solution {
public:

    int beautifulSplits(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> check(n, vector<int>(n, 0));
        for (int x = 0 ; x < n ; ++x) {
            auto & ch = check[x];
            int maxi = x, maxr = x;
            for (int i = x + 1 ; i < n ; ++i) {
                if (maxr >= i) {
                    ch[i] = min(maxr - i + 1, ch[i - maxi + x]);
                }
                while (i + ch[i] < n && nums[i + ch[i]] == nums[ch[i] + x]) ++ch[i];
                if (i + ch[i] - 1 > maxr) {
                    maxi = i;
                    maxr = i + ch[i] - 1;
                }
            }
        }


        int ans = 0;
        for (int i = 0 ; i < n ; ++i) {
            for (int j = i + 1 ; j < n - 1 ; ++j) {
                if (check[0][i + 1] >= i + 1 && j - i >= i + 1 ) {                
                    ++ans;
                    continue ;
                }
                if (check[i+1][j+1] >= j - i) {                
                    ++ans;
                    continue ;
                }
            }
        }

        return ans;
    }
};
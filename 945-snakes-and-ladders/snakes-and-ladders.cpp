class Solution {
private:
    vector<int> conv(int u, int n) {
        int u0 = u - 1;                   // make 0-based
        int rowFromBottom = u0 / n;       // which “strip” from the bottom (0..n-1)
        int offsetInThatRow = u0 % n;     // 0..n-1 within that strip

        // The actual stored board[][] is “top‐down,” so:
        int row = (n - 1) - rowFromBottom;

        // Even‐numbered strips (0,2,4,…) go left→right; odd strips go right→left
        int col;
        if (rowFromBottom % 2 == 0) {
            col = offsetInThatRow; 
        } else {
            col = (n - 1) - offsetInThatRow;
        }

        return { row, col };
    }

public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size(), q = n * n, m = q / 6 + 1;
        vector<int> dp(q, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= m; i++) {
            for (int k = 1; k <= 6; k++) {
                for (int j = 0; j < q-k; j++) {
                    if (dp[j] >= i) continue;
                    int nex = j + 1 + k;
                    vector<int> coord_new = conv(nex, n);
                    int jump = board[coord_new[0]][coord_new[1]];
                    if(jump!=-1){
                        dp[jump-1]=min(dp[jump-1],i);
                    }else{
                        dp[nex-1]=min(dp[nex-1],i);
                    }
                }
            }
        }
        return (dp[q - 1] == INT_MAX ? -1 : dp[q - 1]);
    }
};
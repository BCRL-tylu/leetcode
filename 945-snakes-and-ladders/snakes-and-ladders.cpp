class Solution {
private:
    // ────────────────────────────────────────────────────────────────────────────
    // Replace your old conv(...) with this “1D→2D” implementation.
    //
    // This version guarantees 0 <= row,col < n for every 1 <= u <= n*n.
    //
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
    // ────────────────────────────────────────────────────────────────────────────

public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int q = n * n;                   // total squares = 1..(n*n)
        int m = q / 6 + 1;               // upper‐bound on moves

        // dp[x] = minimum # of dice rolls needed to “land on” square (x+1).
        vector<int> dp(q, INT_MAX);

        // INITIALIZE: square 1 is reached with 0 moves.
        dp[0] = 0;

        // We iterate “move count” i = 1..m.  On move i, only roll dice from squares j
        // for which dp[j] < i (i.e. j was reached in fewer than i moves).
        for (int i = 1; i <= m; i++) {
            for (int k = 1; k <= 6; k++) {
                for (int j = 0; j < q - k; j++) {
                    // ────────────────────────────────────────────────────────────────
                    // Only roll from j if we have actually reached j in < i moves.
                    if (dp[j] >= i) continue;
                    // ────────────────────────────────────────────────────────────────

                    int currSquare = j + 1;            // “j” is 0‐based, so square = j+1
                    int nex = currSquare + k;          

                    // If rolling sends us beyond the last square, skip it.
                    if (nex > q) continue;

                    // Find (row, col) for the “nex”th square:
                    vector<int> coord_new = conv(nex, n);
                    int r = coord_new[0], c = coord_new[1];

                    // If there is a snake/ladder, follow it exactly once:
                    int jump = board[r][c];
                    if (jump != -1) {
                        // “jump” is in [1..n*n], so subtract 1 for 0-based index:
                        dp[jump - 1] = min(dp[jump - 1], i);
                    } else {
                        dp[nex - 1] = min(dp[nex - 1], i);
                    }
                }
            }
        }

        // If we never reached square n*n, dp[n*n -1] is still INT_MAX:
        return (dp[q - 1] == INT_MAX ? -1 : dp[q - 1]);
    }
};

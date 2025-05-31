class Solution {
private:
    vector<int> conv(int u, int n) {
        int u0 = u - 1;                   
        int rowFromBottom = u0 / n;       
        int offsetInThatRow = u0 % n;     

        int row = (n - 1) - rowFromBottom;
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
        int n = board.size();
        int q = n * n;                    // total squares = 1..n*n

        // dist[x] = the minimum # of dice rolls to reach square (x+1), or -1 if unvisited
        vector<int> dist(q, -1);

        // Start on square 1 ⇒ 0 rolls needed
        dist[0] = 0;
        queue<int> bfs;
        bfs.push(1);  // we push the 1‐based square index

        while (!bfs.empty()) {
            int curSquare = bfs.front();
            bfs.pop();

            if (curSquare == q) {
                // As soon as we pop n*n, dist[n*n - 1] is the answer
                return dist[q - 1];
            }

            for (int k = 1; k <= 6; k++) {
                int nxt = curSquare + k;
                if (nxt > q) break;

                // Replace structured binding with explicit indexing
                vector<int> coord = conv(nxt, n);
                int r = coord[0], c = coord[1];

                if (board[r][c] != -1) {
                    nxt = board[r][c];
                }

                if (dist[nxt - 1] == -1) {
                    dist[nxt - 1] = dist[curSquare - 1] + 1;
                    bfs.push(nxt);
                }
            }
        }

        return -1;
    }
};

class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int m = image.size(), n = image[0].size();
        vector<vector<bool>> seen(m, vector<bool>(n, false));
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int minRow = x, maxRow = x;
        int minCol = y, maxCol = y;

        queue<pair<int, int>> q;
        q.emplace(x, y);
        seen[x][y] = true;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;
                if (seen[nr][nc] || image[nr][nc] != '1')
                    continue;
                seen[nr][nc] = true;
                q.emplace(nr, nc);
                minRow = min(minRow, nr);
                maxRow = max(maxRow, nr);
                minCol = min(minCol, nc);
                maxCol = max(maxCol, nc);
            }
        }

        return (maxRow - minRow + 1) * (maxCol - minCol + 1);
    }
};

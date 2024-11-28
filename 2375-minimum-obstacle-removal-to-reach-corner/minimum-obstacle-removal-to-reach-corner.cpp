class Solution {
public:
bool isValid(int x, int y, int m, int n) {
    return x >= 0 && y >= 0 && x < m && y < n;
}
    int minimumObstacles(vector<vector<int>>& grid) {
 int m = grid.size();
    int n = grid[0].size();

    // Directions for neighbors (right, down, left, up)
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Min-heap priority queue: (current weight, x, y)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    // Distance array initialized to infinity
    vector<vector<int>> dist(m, vector<int>(n, numeric_limits<int>::max()));

    // Start from (0, 0) with weight 0
    pq.emplace(0, 0, 0); // (weight, x, y)
    dist[0][0] = 0;

    while (!pq.empty()) {
        auto [currentWeight, x, y] = pq.top();
        pq.pop();

        // If we reach the destination, return the weight
        if (x == m - 1 && y == n - 1) {
            return currentWeight;
        }

        // Skip if we already found a better path
        if (currentWeight > dist[x][y]) continue;

        // Explore neighbors
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (isValid(nx, ny, m, n)) {
                int newWeight = currentWeight + grid[nx][ny]; // Add the edge weight
                if (newWeight < dist[nx][ny]) {
                    dist[nx][ny] = newWeight;
                    pq.emplace(newWeight, nx, ny);
                }
            }
        }
    }
    // If we exit the loop without reaching the destination, there's no path
    return -1; // Or an appropriate indicator for no path
    }
};
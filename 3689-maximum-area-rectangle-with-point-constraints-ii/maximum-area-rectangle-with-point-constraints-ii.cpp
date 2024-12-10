#include <vector>
#include <algorithm>
#include <map>
#include <climits>

class SegTree {
    int n;
    std::vector<long long> tree;

public:
    SegTree(int size) {
        n = 1;
        while (n < size) n <<= 1; // Initialize tree size to the next power of 2
        tree.assign(2 * n, LLONG_MIN);
    }

    void update(int idx, long long val) {
        idx += n;
        while (idx > 0) {
            tree[idx] = std::max(tree[idx], val);
            idx >>= 1;
        }
    }

    long long query(int l, int r) {
        long long res = LLONG_MIN;
        l += n;
        r += n;
        while (r - l > 1) {
            if (l % 2 == 0) res = std::max(res, tree[l + 1]);
            if (r % 2 == 1) res = std::max(res, tree[r - 1]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

class Solution {
public:
    long long maxRectangleArea(std::vector<int>& xCoord, std::vector<int>& yCoord) {
        std::vector<std::pair<int, int>> points;
        for (size_t i = 0; i < xCoord.size(); ++i) {
            points.emplace_back(xCoord[i], yCoord[i]);
        }

        // Sort points by x, then y
        std::sort(points.begin(), points.end());

        // Create unique sorted y-axis and its mapping
        std::vector<int> yAxis = yCoord;
        std::sort(yAxis.begin(), yAxis.end());
        yAxis.erase(std::unique(yAxis.begin(), yAxis.end()), yAxis.end());
        std::map<int, int> yPos;
        for (size_t i = 0; i < yAxis.size(); ++i) {
            yPos[yAxis[i]] = i;
        }

        // Initialize data structures
        std::map<int, long long> yMax; // Maximum x for each y-coordinate
        for (int y : yAxis) {
            yMax[y] = LLONG_MIN;
        }
        SegTree maxTree(yAxis.size());
        int prevX = points[0].first;
        int prevY = points[0].second;
        long long res = -1;

        for (size_t i = 1; i < points.size(); ++i) {
            int x = points[i].first;
            int y = points[i].second;

            if (prevX == x && yMax[prevY] == yMax[y] &&
                yMax[y] > maxTree.query(yPos[prevY], yPos[y])) {
                // x's and y's are aligned
                // and no other points in the rectangle
                res = std::max(res, static_cast<long long>(y - prevY) * (x - yMax[y]));
            }

            // Update the information of (prevX, prevY)
            yMax[prevY] = prevX;
            maxTree.update(yPos[prevY], prevX);
            prevX = x;
            prevY = y;
        }

        return res;
    }
};

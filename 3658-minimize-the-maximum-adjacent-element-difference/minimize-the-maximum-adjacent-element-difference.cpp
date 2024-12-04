class Solution {
public:
bool checkDifference(vector<int>& n, int x, int y, int d) {
    int cnt = 0, prev = 0;
    for (int i = 0; i < n.size(); ++i)
        if (n[i] == -1) {
            if (prev && min(abs(prev - x), abs(prev - y)) > d)
                return false;
            ++cnt;
        }
        else {
            if (cnt) {
                int diff = prev ? min(max(abs(prev - x), abs(n[i] - x)), max(abs(prev - y), abs(n[i] - y)))
                    : min(abs(n[i] - x), abs(n[i] - y));
                if (diff > d && (cnt == 1 || y - x > d))
                    return false;
            } 
            prev = n[i];
            cnt = 0;
        }
    return true;
}
int minDifference(vector<int>& n) {
    int max_gap = 0, min_n = INT_MAX, max_n = 0;
    for (int i = 0; i + 1 < n.size(); ++i) {
        if (min(n[i], n[i + 1]) == -1 && max(n[i], n[i + 1]) != -1) {
            min_n = min(min_n, max(n[i], n[i + 1]));
            max_n = max(max_n, max(n[i], n[i + 1]));
        }
        else
            max_gap = max(max_gap, abs(n[i] - n[i + 1]));
    }
    int l = max_gap, r = (max_n - min_n + 1) / 2;
    while (l < r) {
        int d = (l + r) / 2;
        if (checkDifference(n, min_n + d, max_n - d, d))
            r = d;
        else
            l = d + 1;
    }
    return l;
}
};
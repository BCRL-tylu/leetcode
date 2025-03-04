class Solution {
public:
    long long maxProfit(vector<int>& W, vector<vector<int>>& T) {
        unordered_map<int,int> c;
        for (int a : W) c[a]++;
        unordered_map<int,vector<int>> b;
        for (auto &t : T) b[t[0]].push_back(t[1]);
        long long s = 0;
        int x = 0;
        for (auto &p : b) {
            auto &v = p.second;
            if (c.find(p.first) == c.end())
                x = max(x, *max_element(v.begin(), v.end()));
            else {
                int av = c[p.first], n = v.size();
                if (n <= av)
                    s += accumulate(v.begin(), v.end(), 0LL);
                else {
                    nth_element(v.begin(), v.end() - av, v.end());
                    s += accumulate(v.begin() + n - av, v.end(), 0LL);
                    int m = *max_element(v.begin(), v.begin() + n - av);
                    x = max(x, m);
                }
            }
        }
        return s + x;
    }
};
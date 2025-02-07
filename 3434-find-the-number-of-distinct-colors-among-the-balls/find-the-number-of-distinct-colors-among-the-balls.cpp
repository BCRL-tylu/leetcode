class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int, int> c_i, i_c;
        vector<int> ans;
        int count = 0;

        for (auto& q : queries) {
            int idx = q[0], color = q[1];

            auto it = i_c.find(idx);
            if (it != i_c.end() && it->second == color) {
                ans.push_back(count);
                continue;
            }

            if (c_i.find(color) == c_i.end() || c_i[color] == 0) {
                count++;
            }
            c_i[color]++;

            if (it != i_c.end()) {
                int prevColor = it->second;
                if (--c_i[prevColor] == 0) count--;
            }

            i_c[idx] = color;
            ans.push_back(count);
        }
        return ans;
    }
};

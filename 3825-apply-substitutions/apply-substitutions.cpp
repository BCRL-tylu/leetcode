class Solution {
vector<string> rep{26}, solved{26};
private:
    string dfs(int idx) {
        if (solved[idx] != "") return solved[idx]; // Already expanded
        string v = rep[idx], result;
        for (size_t i = 0; i < v.size();) {
            if (v[i] == '%' ) {
                result += dfs(v[i + 1] - 'A');
                i += 3;
            } else {
                result.push_back(v[i]);
                i++;
            }
        }
        return solved[idx] = result; //fully expanded value
    }

public:
    string applySubstitutions(vector<vector<string>>& replacements,string text) {
        for (auto r : replacements)rep[r[0][0] - 'A'] = r[1];
        for (int i = 0; i < 26; i++) if (!rep[i].empty()) dfs(i);
        string result;
        for (size_t i = 0; i < text.size();) {
            if (text[i] == '%') {
                result += solved[text[i + 1] - 'A'];
                i +=3;
                continue;
            }
            result.push_back(text[i]);
            i++;
        }
        return result;
    }
};
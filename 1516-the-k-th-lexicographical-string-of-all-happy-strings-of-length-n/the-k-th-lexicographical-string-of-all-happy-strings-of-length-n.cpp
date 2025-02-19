char ap[3] = {'a', 'b', 'c'};
const unordered_map<char, vector<char>> m = {
    {'a', {'b', 'c'}},
    {'b', {'a', 'c'}},
    {'c', {'a', 'b'}}
};

class Solution {
public:
    string getHappyString(int n, int k) {
        int ini = 1 << (--n);
        if (k > (ini)*3) return "";
        string ans;

        int ind = (k-1) / (ini);
        ans.push_back(ap[ind]);
        k -= ind * ini;

        for (int i = n; i >= 1; i--) {
            ini>>=1;
            ind = (k-1)/ini;
            k -= ind*ini;
            ans.push_back(m.at(ans.back())[ind]);
        }
        return ans;
    }
};
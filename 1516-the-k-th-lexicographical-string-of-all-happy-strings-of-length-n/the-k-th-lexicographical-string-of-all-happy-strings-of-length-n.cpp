char ap[3] = {'a', 'b', 'c'};
const unordered_map<char, vector<char>> m = {
    {'a', {'b', 'c'}}, {'b', {'a', 'c'}}, {'c', {'a', 'b'}}};

class Solution {
public:
    string getHappyString(int n, int k) {
        int ini = 1 << (n - 1);
        if (k > 3 * ini)
            return ""; // Fix the boundary check

        string ans;
        int ind = (k - 1) / ini;
        ans.push_back(ap[ind]);
        k -= ind * ini; // Adjust k for the remaining sequence

        for (int i = n - 1; i >= 1; i--) {
            ini /= 2;
            ind = (k - 1) / ini;         // Ensure ind remains valid
            k -= ind * ini;              // Adjust k
            ans.push_back(m.at(ans.back())[ind]);
        }
        return ans;
    }
};

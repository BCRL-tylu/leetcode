class Solution {
public:
    string robotWithString(string s) {
        string ts = s, ans;
        char mc = *std::min_element(s.begin(), s.end());
        int u = 0, i = 0, n = s.size();
        stack<char> t;

        vector<char> sm(n, 0);

        char b = s[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            sm[i] = b;
            if (s[i] < b) {
                b = s[i];
            }
        }
        while (s[i] != mc) {
            t.push(s[i++]);
        }
        ans.push_back(mc);
        char nxt = sm[i];
        while (!t.empty() && t.top() <= nxt) {
            ans.push_back(t.top());
            t.pop();
        }
        i++;
        for (; i < n; i++) {
            while (!t.empty() && t.top() <= s[i] && (t.top()<=sm[i]||i==n-1)) {
                ans.push_back(t.top());
                t.pop();
            }
            t.push(s[i]);
        }
        while (!t.empty()) {
            char tp = t.top();
            t.pop();
            ans.push_back(tp);
        }
        return ans;
    }
};
class Solution {
public:
    string robotWithString(string s) {
        int n = s.size();
        if (n == 0) return "";
        vector<char> sm(n+1, '{');
        for (int i = n - 1; i >= 0; --i) {
            sm[i] = (i == n - 1 ? s[i] : min(s[i], sm[i + 1]));
        }


        stack<char> st;
        string ans;
        ans.reserve(n);

        for (int i = 0; i < n; ++i) {
            st.push(s[i]);
            while (!st.empty() && st.top() <= sm[i + 1]) {
                ans.push_back(st.top());
                st.pop();
            }
        }

        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }
};

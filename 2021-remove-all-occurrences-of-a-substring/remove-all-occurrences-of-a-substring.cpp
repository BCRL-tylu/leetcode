class Solution {
public:
    string removeOccurrences(string s, string part) {
        int m = part.size();
        // Build the KMP prefix table for "part"
        vector<int> pi(m, 0);
        for (int i = 1, j = 0; i < m; i++) {
            // If there's a mismatch, fall back to the previous best prefix
            while (j > 0 && part[i] != part[j])
                j = pi[j - 1];
            if (part[i] == part[j])
                pi[i] = ++j;
        }
        
        // Stack (using vector) to keep track of (character, current match length)
        vector<pair<char, int>> st;
        int cur = 0; // current match length with "part"
        
        for (char c : s) {
            // Update the current match length using KMP logic:
            while (cur > 0 && c != part[cur])
                cur = pi[cur - 1];
            if (c == part[cur])
                cur++;
            
            // Push the current character along with the match length so far
            st.push_back({c, cur});
            
            // If we have a full match of "part", remove it from the stack
            if (cur == m) {
                for (int i = 0; i < m; i++) {
                    st.pop_back();
                }
                // Reset cur to the previous match length if available
                cur = st.empty() ? 0 : st.back().second;
            }
        }
        
        // Build the final result from the characters remaining in the stack
        string result;
        for (auto &p : st)
            result.push_back(p.first);
        return result;
    }
};

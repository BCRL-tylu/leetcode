class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        int L = n + m - 1; // length of the generated string
        vector<char> S(L, 0);
        vector<bool> forced(L, false); // true if S[i] is fixed by a 'T' constraint
        
        // Force positions based on 'T' in str1: for each i with str1[i]=='T',
        // S[i...i+m-1] must equal str2.
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    int pos = i + j;
                    char required = str2[j];
                    if (S[pos] == 0) {
                        S[pos] = required;
                        forced[pos] = true;
                    } else {
                        if (S[pos] != required) return ""; // conflict
                    }
                }
            }
        }
        
        // For all positions not forced, assign 'a' (smallest letter)
        for (int pos = 0; pos < L; pos++) {
            if (S[pos] == 0)
                S[pos] = 'a';
        }
        
        // Precompute mismatch counts for every window starting at i (0 <= i < n)
        // mismatch[i] counts the number of positions where S[i...i+m-1] differs from str2.
        vector<int> mismatch(n, 0);
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                if (S[i + j] != str2[j])
                    cnt++;
            }
            mismatch[i] = cnt;
        }
        
        // For every window corresponding to an index i with str1[i]=='F',
        // ensure that the window S[i...i+m-1] is NOT exactly equal to str2.
        // If mismatch[i] == 0, then we need to "fix" that window.
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < n; i++) {
                if (str1[i] == 'F' && mismatch[i] == 0) {
                    int posToChange = -1;
                    // Choose the rightmost free cell (not forced) in the window [i, i+m-1] that is 'a'
                    for (int j = m - 1; j >= 0; j--) {
                        int pos = i + j;
                        if (!forced[pos] && S[pos] == 'a') {
                            posToChange = pos;
                            break;
                        }
                    }
                    if (posToChange == -1)
                        return ""; // No valid fix possible
                    
                    // Change S[posToChange] from 'a' to 'b'
                    S[posToChange] = 'b';
                    
                    // Update mismatch counts for all windows that include posToChange.
                    // A cell at pos belongs to all windows starting from max(0, pos-m+1) to min(n-1, pos).
                    int start = max(0, posToChange - m + 1);
                    int end = min(n - 1, posToChange);
                    for (int i2 = start; i2 <= end; i2++) {
                        int j = posToChange - i2; // index in the window
                        // When the cell was 'a', its contribution was 0 if str2[j]=='a', else 1.
                        int oldContrib = (str2[j] == 'a' ? 0 : 1);
                        // Now that it is 'b', contribution is 0 if str2[j]=='b', else 1.
                        int newContrib = (str2[j] == 'b' ? 0 : 1);
                        mismatch[i2] = mismatch[i2] - oldContrib + newContrib;
                    }
                    changed = true;
                    // Restart checking from the beginning after a change.
                    break;
                }
            }
        }
        
        // Final verification: for each window, ensure that:
        // - If str1[i]=='T', then S[i...i+m-1] equals str2.
        // - If str1[i]=='F', then S[i...i+m-1] does not equal str2.
        for (int i = 0; i < n; i++) {
            bool equal = true;
            for (int j = 0; j < m; j++) {
                if (S[i + j] != str2[j]) {
                    equal = false;
                    break;
                }
            }
            if (str1[i] == 'T' && !equal)
                return "";
            if (str1[i] == 'F' && equal)
                return "";
        }
        
        return string(S.begin(), S.end());
    }
};

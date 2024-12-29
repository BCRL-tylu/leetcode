class Solution {
public:
    int numWays(vector<string>& words, string target) {
        const int mod = 1e9 + 7;

        int n = target.size();
        int m = words[0].size();

        // Step 1: Build frequency table for each column
        std::vector<std::vector<int>> columnCharCount(m, std::vector<int>(26, 0));
        for (const std::string& word : words) {
            for (int col = 0; col < m; ++col) {
                columnCharCount[col][word[col] - 'a']++;
            }
        }
        // Step 2: Use a single DP array
        std::vector<int> charArray(n, 0);
        for (int i = 0; i < m; ++i) {
            // Update charArray in reverse to avoid overwriting dependencies
            for (int j = n - 1; j >= 0; --j) {
                if (j == 0) {
                    // First character of target
                    charArray[0] = (charArray[0] + columnCharCount[i][target[0] - 'a']) % mod;
                } else if (charArray[j - 1] > 0) {
                    // Other characters of target
                    charArray[j] = (charArray[j] + 1LL * charArray[j - 1] * columnCharCount[i][target[j] - 'a'] % mod) % mod;
                }
            }
        }
        return charArray[n - 1];
    }
};

class Solution {
public:
    int numWays(vector<string>& words, string target) {
        int mod = 1e9 + 7;

        // Step 1: Count character frequencies in each column
        std::unordered_map<int, std::unordered_map<char, int>> columnCharCount;
        for (const std::string& word : words) {
            for (int col = 0; col < word.size(); ++col) {
                char ch = word[col];
                columnCharCount[col][ch]++;
            }
        }

        int n = target.size();
        int m = words[0].size();
        std::vector<int> charArray(n, 0);

        // Step 2: Iterate through columns
        for (int i = 0; i < m; ++i) {
            std::vector<int> temparr = charArray; // Copy current state
            auto& col_hm = columnCharCount[i];   // Reference to column hashmap
            
            // Update first character
            charArray[0] = (charArray[0] + col_hm[target[0]]) % mod;

            // Update remaining characters
            for (int j = 1; j < n; ++j) {
                if (temparr[j - 1] > 0) { // Check if previous state exists
                    char selectchar = target[j];
                    charArray[j] = (charArray[j] + (1LL * temparr[j - 1] * col_hm[selectchar]) % mod) % mod;
                }
            }
        }
        return charArray[n - 1];
    }
};

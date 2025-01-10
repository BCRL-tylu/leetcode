class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        vector<int> w2m(26); // Maximum frequency of each letter across all words in words2

        // Build the maximum frequency vector for words2
        for (const string& word : words2) {
            vector<int> current_vec(26);
            for (char c : word) {
                current_vec[c - 'a']++;
                w2m[c - 'a'] = max(w2m[c - 'a'], current_vec[c - 'a']);
            }
        }

        vector<string> ans;

        // Iterate through words1 and check if they are universal
        for (const string& word : words1) {
            vector<int> current_vec1(26);
            for (char c : word) {
                current_vec1[c - 'a']++;
            }

            // Check if word satisfies the maximum frequency constraints
            bool isUniversal = true;
            for (int i = 0; i < 26; ++i) {
                if (current_vec1[i] < w2m[i]) {
                    isUniversal = false;
                    break;
                }
            }

            if (isUniversal) {
                ans.push_back(word);
            }
        }

        return ans;
    }
};

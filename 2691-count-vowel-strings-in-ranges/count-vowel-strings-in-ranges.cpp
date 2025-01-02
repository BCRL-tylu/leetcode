class Solution {

public:
    vector<int> vowelStrings(vector<string>& words,
                             vector<vector<int>>& queries) {
        auto isVowel = [](char ch) {
            return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' ||
                   ch == 'u';
        };
        int n = words.size();
        vector<int> prefixsum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            if (isVowel(words[i].front()) && isVowel(words[i].back())) {
                prefixsum[i + 1] = prefixsum[i] + 1;
            } else {
                prefixsum[i + 1] = prefixsum[i];
            }
        }
        int k = queries.size();
        vector<int> ans(k, -1);
        for (int j = 0; j < k; j++) {
            ans[j] = prefixsum[queries[j][1] + 1] - prefixsum[queries[j][0]];
        }
        return ans;
    }
};
class Solution {
private:
bool vo(const std::string& str) {
    // Helper lambda to check if a character is a vowel
    auto isVowel = [](char ch) {
        ch = std::tolower(ch); // Convert to lowercase
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    };

    // Check if first and last characters are vowels
    return isVowel(str.front()) && isVowel(str.back());
}

public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        int n = words.size();
        vector<int> prefixsum(n+1,0);
        for(int i = 0; i<n;i++){
            if(vo(words[i])){
                prefixsum[i+1] = prefixsum[i]+1;
            }else{
                prefixsum[i+1] = prefixsum[i];
            }
        }
        int k = queries.size();
        vector<int> ans(k,-1);
        for(int j = 0; j<k;j++){
            ans[j] = prefixsum[queries[j][1]+1] - prefixsum[queries[j][0]];
        }
        return ans;
    }
};
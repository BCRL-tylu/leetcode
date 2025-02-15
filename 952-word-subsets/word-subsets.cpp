class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        vector<int> w2m(26);
        int m = words2.size(), n= words1.size();

        for(int i =0; i<m;i++){
            vector<int> current_vec(26);
            string temp_word = words2[i];
            for(int j =0;j<temp_word.size();j++){
                int now = temp_word[j]-'a';
                w2m[now] = max(w2m[now],++current_vec[now]);
            }
        }
        vector<string> ans;
        int sz = w2m.size();
        vector<int> nonZeroIndices;

    // Collect indices of non-zero elements
    for (size_t i = 0; i < sz; ++i) {
        if (w2m[i] != 0) {
            nonZeroIndices.push_back(i);
        }
    }
        for(int i = 0; i<n;i++){
            vector<int> current_vec1(26);
            string temp_word1 = words1[i];
            for(int j =0;j<temp_word1.size();j++){
                current_vec1[temp_word1[j]-'a']++;
            }
            bool p = true;
            for(int k :nonZeroIndices){
                if(current_vec1[k]<w2m[k]){
                    p = false;
                    break;
                }
            }
            if(p) ans.push_back(temp_word1);
        }
        return ans;
    }
};



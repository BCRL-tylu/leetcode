class Solution {
public:
    long long countOfSubstrings(string word, int k) {
        auto f = [&](int k) -> long long{
            long long ans = 0, left = 0, vowel = 0, consonants = 0;
            vector<int> freq('v');

            for(char &w : word){
                if(w != 'a' && w != 'e' && w != 'i' && w != 'o' && w != 'u') consonants++;
                else if(++freq[w] == 1) vowel++;
                while((vowel == 5) && (consonants >= k)){
                    char c = word[left++];
                    if(c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') consonants--;
                    else if(--freq[c] == 0) vowel--;
                }
                ans += left;
            }
            return ans;
        };

        return f(k) - f(k + 1);
    }
};
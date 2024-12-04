class Solution {
public:
    bool canMakeSubsequence(string& str1, string& str2) {
        int i {0};

        auto next_cyclic_char {[](char c) -> char {
            if (c == 'z')
                return 'a';
            else
                return c+1;
        }};

        for (const int subseq_len = str2.size(); auto c : str1) {
            if (c == str2[i] || next_cyclic_char(c) == str2[i])
                ++i;

            if (i == subseq_len)
                return true;
        }

        return false;
    }
};
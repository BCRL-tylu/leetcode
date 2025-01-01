#include <string>
#include <algorithm>

class Solution {
public:
    std::string answerString(std::string word, int numFriends) {
        return sln1(word, numFriends);
    }

private:
    std::string sln1(const std::string& s, int l) {
        if (l == 1) return s;

        int k = 0;
        int i = 0;
        int j = 1;
        int n = s.length();

        while (j + k < n) {
            int diff = s[i + k] - s[j + k];
            if (diff == 0) {
                k++;
            } else if (diff > 0) {
                j = j + k + 1;
                k = 0;
            } else {
                i = std::max(i + k + 1, j);
                j = i + 1;
                k = 0;
            }
        }

        return s.substr(i, std::min(n, i + n - l + 1) - i);
    }
};

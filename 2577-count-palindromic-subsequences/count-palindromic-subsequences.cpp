class Solution {
public:
    int countPalindromes(const string& s) {
        #define num(c) size_t(c - 48)
        array<int, 10> leftNumCnt, rightNumCnt, leftPrs[10], rightPrs[10];
        long result = 0;
        for (const char& digit : s) {
            for (size_t i = 0; i <= 9; ++i) rightPrs[i][num(digit)] += rightNumCnt[i];
            ++rightNumCnt[num(digit)];
        }
        for (const char& digit : s) {
            --rightNumCnt[num(digit)];
            for (size_t ind = 0; int& i : rightPrs[num(digit)]) i -= rightNumCnt[ind++];
            for (size_t i = 0; i <= 9; ++i) for (size_t j = 0; j <= 9; ++j) result += (long) rightPrs[i][j] * leftPrs[i][j];
            for (size_t ind = 0; int& i : leftPrs[num(digit)]) i += leftNumCnt[ind++];
            ++leftNumCnt[num(digit)];
        }
        return result % 1000000007;
    }
};
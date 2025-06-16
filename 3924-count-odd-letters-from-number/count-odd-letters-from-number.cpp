class Solution {
public:
    int countOddLetters(int n) {
        unordered_map<int, string> mp = {
            {0, "zero"}, {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"},
            {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}};
        vector<int> cnt(26, 0);
        while (n) {
            string scur = mp[n % 10];
            n /= 10;
            for (const char& c : scur)
                cnt[c - 'a']++;
        }
        int res = 0;
        for (int i = 0; i < 26; i++)
            if (cnt[i] & 1)
                res++;
        return res;
    }
};
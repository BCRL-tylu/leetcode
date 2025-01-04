class Solution {
public:
    int myAtoi(const string& s) {
        bool isNeg = false;
        int i = 0, sz = s.size();
        while (i < sz && s[i] == ' ') ++i;

        if (i >= sz) return 0;
        if (s[i] == '-') isNeg = true;
        if (s[i] == '-' || s[i] == '+') ++i;

        while (i < sz && s[i] == '0') ++i;

        int64_t ret = 0, maxValue = (int64_t)INT32_MAX + 1;
        while (i < sz && '0' <= s[i] && s[i] <= '9'
                && ret <= maxValue) {
            ret = ret * 10 + (s[i] - '0');
            ++i;
        }
        if (isNeg) ret = -ret;
        if (ret < INT32_MIN) return INT32_MIN;
        if (ret > INT32_MAX) return INT32_MAX;
        return ret;
    }
};
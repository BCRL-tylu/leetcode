class Solution {
private:
    std::string toBaseK(long long x, int k) {
        assert(k >= 2 && k <= 9);
        if (x == 0) return "0";
        std::string s;
        while (x > 0) {
            int d = x % k;
            s.push_back(char('0' + d));
            x /= k;
        }
        std::reverse(s.begin(), s.end());
        return s;
    }

    bool isPalindrome(const std::string &s) {
        return std::equal(s.begin(), s.end(), s.rbegin());
    }

public:
    long long kMirror(int k, int n) {
        std::vector<long long> found;
        for (int len = 1; found.size() < n; ++len) {
            int half = (len + 1) / 2;
            int start = (half == 1 ? 1 : int(std::pow(10, half-1)));
            int end   = int(std::pow(10, half)) - 1;
            for (int prefix = start;
                 prefix <= end && found.size() < n;
                 ++prefix) {
                std::string s = std::to_string(prefix);
                std::string t = s.substr(0, len % 2 ? s.size()-1 : s.size());
                std::reverse(t.begin(), t.end());
                long long pal = std::stoll(s + t);

                auto bk = toBaseK(pal, k);
                if (isPalindrome(bk))
                    found.push_back(pal);
            }
        }
        return std::accumulate(found.begin(), found.end(), 0LL);
    }
};

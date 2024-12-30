class Solution {
public:
    string convert(string s, int numRows) {
        std::reverse(s.begin(), s.end());
        std::vector<string> vec(numRows);
        while (!s.empty()) {
            int position = 0;
            while (position < numRows && !s.empty()) {
                char e = s.back();
                s.pop_back();
                vec[position] += e;
                position ++;
            }
            position -= 2;
            while (position >= 1 && !s.empty()) {
                char m = s.back();
                s.pop_back();
                vec[position] += m;
                position--;
            }
        }
        std::string result;
        for (const auto& str : vec) {
            result += str; // Append each string to the result
        }
        return result;
    }
};
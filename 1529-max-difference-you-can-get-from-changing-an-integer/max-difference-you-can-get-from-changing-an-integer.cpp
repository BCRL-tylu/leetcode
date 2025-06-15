class Solution {
public:
    int maxDiff(int num) {
        string s = to_string(num);

        string hi = s;
        char tgt = ' ';
        for (char c : s) {
            if (c != '9') {
                tgt = c;
                break;
            }
        }
        if (tgt != ' ') {
            for (char& c : hi)
                if (c == tgt)
                    c = '9';
        }
        long long maxVal = stoll(hi);

        string lo = s;
        tgt = ' ';
        for (char c : s) {
            if (c > '1') {
                tgt = c;
                break;
            }
        }
        bool di = false;
        if (tgt != s[0]) {
            di = true;
        }
        if (tgt != ' ') {
            for (char& c : lo) {
                if (c == tgt) {
                if(di){
                    c = '0';
                }else{
                    c ='1';
                }
                }
            }
        }
        long long minVal = stoll(lo);

        return static_cast<int>(maxVal - minVal);
    }
};
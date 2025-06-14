class Solution {
public:
    int minMaxDifference(int num) {
        string s = to_string(num);

        /* ----- build the maximum value ----- */
        string hi = s;
        char tgt = ' ';
        for (char c : s) {           // first non‑9
            if (c != '9') { tgt = c; break; }
        }
        if (tgt != ' ') {
            for (char &c : hi) if (c == tgt) c = '9';
        }
        long long maxVal = stoll(hi);   // stoll avoids overflow

        /* ----- build the minimum value ----- */
        string lo = s;
        tgt = ' ';
        for (char c : s) {           // first non‑0
            if (c != '0') { tgt = c; break; }
        }
        if (tgt != ' ') {
            for (char &c : lo) if (c == tgt) c = '0';
        }
        long long minVal = stoll(lo);

        return static_cast<int>(maxVal - minVal);
    }
};

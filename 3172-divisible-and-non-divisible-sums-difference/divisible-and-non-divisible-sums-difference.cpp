class Solution {
public:
    int differenceOfSums(int n, int m) {
        int div = n / m, rem = n % m, ele = div * m;

        int add = (rem > 0)? ((2 * ele + rem + 1) * rem / 2): 0;

        return ele * (ele - 1 - 2 * div) / 2 + add;

        // return div * div * m * (m - 1) / 2 + add - ((1 + div) * div / 2) * m;
    }
};
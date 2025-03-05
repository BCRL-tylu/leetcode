class Solution {
public:
    long long coloredCells(int n) {
        long long k = (long long)n*n;
        return 2*k-(n<<1)+1;
    }
};
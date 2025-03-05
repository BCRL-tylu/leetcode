class Solution {
public:
    long long coloredCells(int n) {
        long long k = (long long)n*n<<1;
        return k-(n<<1)+1;
    }
};
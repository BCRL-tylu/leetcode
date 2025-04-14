const int MOD = 1e9 + 7;
class Solution {
private:


long long mod_pow(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}
public:
    int countGoodNumbers(long long n) {
    long long even_positions = (n + 1) / 2; 
    long long odd_positions = n / 2;     

    long long part1 = mod_pow(5, even_positions);
    long long part2 = mod_pow(4, odd_positions);

    long long answer = (part1 * part2) % MOD;
    return (int)answer;
    }
};
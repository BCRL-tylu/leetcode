class Solution {
public:
    int reverse(int x) {
        int ret = 0;

        while (x != 0) {
            int digit = x % 10; // Get the last digit
            x /= 10; // Remove the last digit from x

            // Check for overflow
            if (ret > INT_MAX / 10 || (ret == INT_MAX / 10 && digit > 7)) {
                return 0; // Overflow case
            }
            if (ret < INT_MIN / 10 || (ret == INT_MIN / 10 && digit < -8)) {
                return 0; // Underflow case
            }

            ret = ret * 10 + digit; // Append the digit
        }
        
        return ret;
    }
};

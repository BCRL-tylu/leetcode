class Solution {
private:
    int digit[100];

public:
    long long kMirror(int k, int n) {
        auto isPalindrome = [&](long long x) -> bool {
            int length = -1;
            while (x) { 
                ++length; 
                digit[length] = x % k; // find the remind of least significant bit
                x /= k; // shift >>1 in base k
            }
            for (int i = 0, j = length; i < j; ++i, --j) { // palindrome check
                if (digit[i] != digit[j]) {
                    return false;
                }
            }
            return true;
        };

        int left = 1, count = 0;
        long long ans = 0;
        while (count < n) {// check counts of palidrome found
            int right = left * 10;
            // op = 0 表示枚举奇数长度回文，op = 1 表示枚举偶数长度回文
            // picking the digits from 1-10, 10-100 even, 100-1000 odd, 1000-10000 even etc
            //left=1, right=10
            //left=10, right=100
            //left=100, right=1000
            for (int op = 0; op < 2; ++op) {
                // 枚举 i'
                for (int i = left; i < right && count < n; ++i) {
                    long long combined = i;
                    int x = (op == 0 ? i / 10 : i); // if odd we have x = i/10, otherwise x =i

                    // combined = left+x
                    // e.g when even we pick 1000-9999 + 1000-9999 to make it palindrome so x = i
                    // else when odd. we pick 1000-9999 (contains a middle value) + 100-999 so x = i/10
                    while (x) {
                        // combined*10 =left shift by 1, append the last digit of x - palidrome
                        // e.g i = abcd then x = abcd or abc
                        // we append abdc<<1 ->abcd0, then append last digit of x
                        // hence the combined is garentee palidrom in base 10
                        combined = combined * 10 + x % 10;
                        x /= 10;
                    }
                    // check palidrom in base k
                    if (isPalindrome(combined)) {
                        ++count;
                        ans += combined;
                    }
                }
            }
            // proceed left to right
            left = right;
        }
        return ans;
    }
};
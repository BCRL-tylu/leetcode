#include <array>       // For using std::array
#include <cstdint>     // For uint64_t
#include <string>      // For std::string
using namespace std;   // Use the standard namespace

// Define a type alias for unsigned 64-bit integers
typedef uint64_t u64;

// Define constants
constexpr u64 mod = 1e9 + 7;  // Modulo value to prevent overflow
constexpr u64 n = 800;         // Maximum limit for set bits we are interested in

// Precompute the minimum number of operations to reduce an integer to 1
constexpr auto dp = [] {
    array<u64, n + 1> dp{};  // Create an array to store the operations needed for each integer
    for (u64 i = 2; i <= n; i++) {
        dp[i] = dp[__builtin_popcount(i)] + 1;  // Use the number of set bits to find the number of operations
    }
    return dp;  // Return the filled dp array
}();

// Precompute binomial coefficients
auto C = [] {
    array<array<u64, n + 1>, n + 1> C{};  // 2D array for binomial coefficients
    C[0][0] = C[1][0] = C[1][1] = 1;  // Base cases
    for (u64 i = 2; i <= n; i++) {
        C[i][0] = 1;  // C(i, 0) is always 1
        for (u64 j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];  // Compute binomial coefficient using recursion
            C[i][j] %= mod;  // Apply modulo to prevent overflow
        }
    }
    return C;  // Return the filled binomial coefficient array
}();

// Define the solution class
class Solution {
public:
    // Method to count k-reducible numbers
    u64 countKReducibleNumbers(string s, u64 k) {
        u64 n = s.size();  // Get the size of the input string
        u64 c1 = 0;  // Counter for the number of 1s encountered
        u64 ans = 0;  // Variable to hold the result count
        
        // Iterate through each character in the binary string
        for (u64 i = 0; i < n; i++) {
            // Check if the current character is '1'
            if (s[i] == '1') {
                // Check subsequent characters to count possible zeros
                for (u64 c2 = 0; i + c2 < n; c2++) {
                    // Check if the current combination can be reduced to 1 in at most k operations
                    if (c1 + c2 > 0 && dp[c1 + c2] + 1 <= k) {
                        ans += C[n - i - 1][c2];  // Add the number of combinations to ans
                        ans %= mod;  // Apply modulo to the result
                    }
                }
                c1++;  // Increment the counter for 1s
            }
        }
        
        return ans;  // Return the total count of k-reducible numbers
    }
};

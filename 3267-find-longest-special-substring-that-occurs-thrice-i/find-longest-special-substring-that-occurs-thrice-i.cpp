#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

class Solution {
public:
    std::vector<int> computeZArray(const std::string& s) {
        int n = s.size();
        std::vector<int> Z(n, 0);
        int l = 0, r = 0; // Window [l, r] with Z-box

        for (int i = 1; i < n; ++i) {
            if (i <= r) {
                Z[i] = std::min(r - i + 1, Z[i - l]);
            }
            while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
                ++Z[i];
            }
            if (i + Z[i] - 1 > r) {
                l = i;
                r = i + Z[i] - 1;
            }
        }
        return Z;
    }

    int findMaxI(const std::vector<int>& vec) {
        std::vector<int> count(vec.size() + 1, 0);
        for (int num : vec) {
            if (num >= 0 && num < count.size()) {
                count[num]++;
            }
        }

        int totalCount = 0;
        for (int i = count.size() - 1; i >= 0; --i) {
            totalCount += count[i];
            if (totalCount >= 3) {
                return i; // Found the largest i with at least 3 occurrences
            }
        }
        return 0; // No such i found
    }

    int maximumLength(std::string s) {
        int n = s.size();
        if (n == 0) return -1; // Handle edge case for empty string
        
        std::string cp;
        cp += s[0]; // Start with the first character
        std::vector<int> z_ind;
        int rtsz = -1;

        for (int i = 1; i < n; ++i) {
            if (s[i] != cp.back() || i == (n - 1)) {
                std::string combined = cp + "$" + s; // Combine current pattern and input string
                z_ind = computeZArray(combined);
                z_ind.erase(z_ind.begin(), z_ind.begin() + cp.size() + 1); // Remove prefix Z values
                rtsz = std::max(rtsz, findMaxI(z_ind));
                cp = s[i]; // Start a new current pattern
            } else {
                cp += s[i]; // Extend the current pattern
            }
        }
        return (rtsz == 0) ? -1 : rtsz; // Return -1 if no valid length found
    }
};

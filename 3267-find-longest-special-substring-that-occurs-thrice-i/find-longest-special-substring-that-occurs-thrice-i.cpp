#include <vector>
#include <string>
#include <algorithm>

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
        int maxI = 0;
        for (int i = 1; ; ++i) {
            int count = std::count_if(vec.begin(), vec.end(), [i](int num) {
                return num >= i;
            });
            if (count >= 3) {
                maxI = i; 
            } else {
                break; 
            }
        }
        return maxI; 
    }

    int maximumLength(std::string s) {
        int n = s.size();
        std::string cp ; // Current pattern
        cp = s[0];
        std::string combined;
        std::vector<int> z_ind;
        int rtsz = -1;
        for (int i = 1; i < n; i++) {
            if (s[i] != cp.back()||i==(n-1)) {
                combined = cp + "$" + s; // Combine current pattern and input string
                z_ind = computeZArray(combined);
                z_ind = vector<int>(z_ind.begin()+cp.size(), z_ind.end());
                rtsz = std::max(rtsz, findMaxI(z_ind));
                cp = s[i]; // Start a new current pattern
            } else {
                cp += s[i]; // Extend the current pattern
            }
        }
        if(rtsz == 0){
            return -1;
        }
        return rtsz;
    }
};

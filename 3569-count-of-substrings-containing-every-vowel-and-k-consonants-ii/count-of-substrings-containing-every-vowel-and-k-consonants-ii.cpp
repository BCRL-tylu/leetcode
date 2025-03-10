#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long countOfSubstrings(string word, int k) {
        int n = word.size();
        // prefixCons[i] = number of consonants in word[0...i-1]
        vector<int> prefixCons(n + 1, 0);
        // For vowels, we maintain 5 prefix arrays corresponding to 'a', 'e', 'i', 'o', 'u'
        vector<vector<int>> prefixV(5, vector<int>(n + 1, 0));
        
        auto isVowelChar = [&](char c) -> int {
            if(c == 'a') return 0;
            if(c == 'e') return 1;
            if(c == 'i') return 2;
            if(c == 'o') return 3;
            if(c == 'u') return 4;
            return -1; // not a vowel
        };
        
        // Build prefix arrays.
        for (int i = 0; i < n; i++) {
            prefixCons[i + 1] = prefixCons[i] + (isVowelChar(word[i]) == -1 ? 1 : 0);
            for (int v = 0; v < 5; v++) {
                prefixV[v][i + 1] = prefixV[v][i];
            }
            int vid = isVowelChar(word[i]);
            if (vid != -1)
                prefixV[vid][i + 1]++;
        }
        
        auto validVowels = [&](int i, int j) -> bool {
            for (int v = 0; v < 5; v++) {
                if (prefixV[v][j + 1] - prefixV[v][i] < 1)
                    return false;
            }
            return true;
        };
        
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int target = prefixCons[i] + k;
            // Find the range in prefixCons (with index r = j+1) where prefixCons[r] == target.
            auto it_low = lower_bound(prefixCons.begin() + i + 1, prefixCons.end(), target);
            if (it_low == prefixCons.end() || *it_low != target)
                continue;  // no substring starting at i has exactly k consonants
            auto it_high = upper_bound(prefixCons.begin() + i + 1, prefixCons.end(), target);
            auto lo = it_low, hi = it_high;
            while (lo < hi) {
                auto mid = lo + (hi - lo) / 2;
                int j = (mid - prefixCons.begin()) - 1; // since prefixCons index = j+1.
                if (validVowels(i, j))
                    hi = mid;
                else
                    lo = mid + 1;
            }
            if (lo == it_high)
                continue;
            ans += (it_high - lo);
        }
        
        return ans;
    }
};

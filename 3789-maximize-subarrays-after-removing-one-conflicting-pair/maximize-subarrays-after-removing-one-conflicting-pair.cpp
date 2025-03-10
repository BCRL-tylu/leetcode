#include <bits/stdc++.h>
using namespace std;
 
class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        int m = conflictingPairs.size();
        for (auto &cp : conflictingPairs) {
            if(cp[0] > cp[1]) swap(cp[0], cp[1]);
        }
        sort(conflictingPairs.begin(), conflictingPairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
 
        vector<int> f(n+1, 0), g(n+1, 0), cnt(n+1, 0);
 
        int idx = 0;
        int currentMax = 0, secondMax = 0, freq = 0;
        for (int j = 1; j <= n; j++) {
            while (idx < m && conflictingPairs[idx][1] == j) {
                int a_val = conflictingPairs[idx][0];
                if(a_val > currentMax) {
                    secondMax = currentMax;
                    currentMax = a_val;
                    freq = 1;
                } else if(a_val == currentMax) {
                    freq++;
                } else if(a_val > secondMax) {
                    secondMax = a_val;
                }
                idx++;
            }
            f[j] = currentMax;
            g[j] = secondMax;
            cnt[j] = freq;
        }
 
        long long base = 0;
        for (int j = 1; j <= n; j++) {
            base += (j - f[j]);
        }
 
        vector<vector<pair<int, long long>>> bonusForA(n+1);
        for (int j = 1; j <= n; j++) {
            if (f[j] > 0 && cnt[j] == 1) {
                long long bonus = (long long)f[j] - g[j];
                bonusForA[f[j]].push_back({j, bonus});
            }
        }
        vector<vector<long long>> prefix(n+1);
        for (int a = 1; a <= n; a++) {
            if (!bonusForA[a].empty()) {
                sort(bonusForA[a].begin(), bonusForA[a].end(), [](auto &p1, auto &p2) {
                    return p1.first < p2.first;
                });
                int sz = bonusForA[a].size();
                prefix[a].resize(sz);
                prefix[a][sz-1] = bonusForA[a][sz-1].second;
                for (int i = sz-2; i >= 0; i--) {
                    prefix[a][i] = prefix[a][i+1] + bonusForA[a][i].second;
                }
            }
        }
 
        long long bestBonus = 0;
        for (auto &cp : conflictingPairs) {
            int a = cp[0], b = cp[1];
            // Query bonusForA[a] for indices j >= b.
            long long candidateBonus = 0;
            auto &vec = bonusForA[a];
            if (!vec.empty()) {
                // binary search for first index with j >= b
                int lo = 0, hi = vec.size()-1, pos = vec.size();
                while (lo <= hi) {
                    int mid = (lo+hi)/2;
                    if (vec[mid].first >= b) {
                        pos = mid;
                        hi = mid-1;
                    } else {
                        lo = mid+1;
                    }
                }
                if (pos < vec.size()) {
                    candidateBonus = prefix[a][pos];
                }
            }
            bestBonus = max(bestBonus, candidateBonus);
        }
 
        return base + bestBonus;
    }
};

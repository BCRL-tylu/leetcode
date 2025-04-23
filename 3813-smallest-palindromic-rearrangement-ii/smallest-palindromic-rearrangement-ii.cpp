#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;
const ld INF = 1e18;

class Solution {
private:
ll countPerm(const vector<int>& cnt, ll k,
              const vector<double>& logFact,
              double logK)
{
    int rem = 0;
    for (int x : cnt) rem += x;

    // Quick check via logs: if log( rem! / ∏ (cnt[i]! ) ) > logK,
    // then the true count > k, so we can bail out.
    double logM = logFact[rem];
    for (int x : cnt) {
        if (x > 0) logM -= logFact[x];
    }
    if (logM > logK + 1e-12) 
        return k + 1;

    // Otherwise the count is ≤ k, so compute it exactly.
    ll result = 1;
    int slots = rem;
    for (int x : cnt) {
        if (x == 0) continue;
        // compute C(slots, x) capped at k+1
        ll comb = 1;
        // use the multiplicative formula:
        //   C(n, r) = ∏_{i=1..r} (n-r+i)/i
        for (int i = 1; i <= x; i++) {
            comb = comb * (slots - x + i) / i;
            if (comb > k) {
                comb = k + 1;
                break;
            }
        }
        result = result * comb;
        if (result > k) 
            return k + 1;
        slots -= x;
    }
    return result;
}

public:
    string smallestPalindrome(string s, int k) {
    
int n = s.size();
   k = (long long)k;
    // 1) Count frequencies
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    // 2) Pull out the middle character (if any)
    char mid = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2) {
            mid = 'a' + i;
            freq[i]--;
            break;
        }
    }

    // 3) Build half‐counts
    vector<int> halfCnt(26, 0);
    int halfLen = 0;
    for (int i = 0; i < 26; i++) {
        halfCnt[i] = freq[i] / 2;
        halfLen += halfCnt[i];
    }

    // 4) Precompute log factorial up to halfLen
    vector<double> logFact(halfLen + 1, 0.0);
    for (int i = 1; i <= halfLen; i++) {
        logFact[i] = logFact[i - 1] + log((double)i);
    }
    double logK = log((double)k);

    // 5) If total palindromic perms < k, print empty
    if (countPerm(halfCnt, k, logFact, logK) < k) {
        cout << "\n";
        return "";
    }

    // 6) Build the k-th lexicographic half‐string
    string half;
    half.reserve(halfLen);
    for (int pos = 0; pos < halfLen; pos++) {
        for (int c = 0; c < 26; c++) {
            if (halfCnt[c] == 0) continue;
            halfCnt[c]--;
            ll cnt = countPerm(halfCnt, k, logFact, logK);
            if (cnt >= k) {
                half.push_back('a' + c);
                break;
            } else {
                k -= cnt;
                halfCnt[c]++;
            }
        }
    }

    // 7) Mirror + middle
    string rev = half;
    reverse(rev.begin(), rev.end());
    string result = half + (mid ? string(1, mid) : "") + rev;
    return result;
    }
};
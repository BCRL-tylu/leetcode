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
    double logM = logFact[rem];
    for (int x : cnt) {
        if (x > 0) logM -= logFact[x];
    }
    if (logM > logK + 1e-12) 
        return k + 1;
    ll result = 1;
    int slots = rem;
    for (int x : cnt) {
        if (x == 0) continue;
        ll comb = 1;
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
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    char mid = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2) {
            mid = 'a' + i;
            freq[i]--;
            break;
        }
    }

    vector<int> halfCnt(26, 0);
    int halfLen = 0;
    for (int i = 0; i < 26; i++) {
        halfCnt[i] = freq[i] / 2;
        halfLen += halfCnt[i];
    }

    vector<double> logFact(halfLen + 1, 0.0);
    for (int i = 1; i <= halfLen; i++) {
        logFact[i] = logFact[i - 1] + log((double)i);
    }
    double logK = log((double)k);

    if (countPerm(halfCnt, k, logFact, logK) < k) {
        cout << "\n";
        return "";
    }

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
    string rev = half;
    reverse(rev.begin(), rev.end());
    string result = half + (mid ? string(1, mid) : "") + rev;
    return result;
    }
};
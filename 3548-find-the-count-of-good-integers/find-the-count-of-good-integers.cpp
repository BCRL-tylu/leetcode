#include <vector>
#include <set>
#include <array>
using namespace std;

class Solution {
public:
    // We precompute factorials up to 10! (n ≤ 10)
    long long fact[11];
    
    // Global variables used in the recursion
    int N, K, L; // N = n, K = k, L = number of digits in half (ceil(n/2))
    vector<int> pow10_mod;       // pow10_mod[i] = 10^i mod k for i in [0, n-1]
    vector<int> contribution;    // contribution for each half-digit position
    set<array<int, 10>> freqSet; // unique frequency vectors (multisets)
    
    // Precompute factorial values [0 ... n] for n up to 10.
    void initFactorials() {
        fact[0] = 1;
        for (int i = 1; i <= 10; i++) {
            fact[i] = fact[i - 1] * i;
        }
    }
    
    // Given a completed half-digit vector, build the full palindrome
    // and record its digit frequency if the entire number is divisible by k.
    void processFullNumber(const vector<int>& half, int n) {
        vector<int> full;
        if(n % 2 == 0) {
            // even-length palindrome
            full = half;
            for (int i = (int)half.size() - 1; i >= 0; i--) {
                full.push_back(half[i]);
            }
        } else {
            // odd-length: the last digit of half is the middle digit
            for (int i = 0; i < (int)half.size() - 1; i++) {
                full.push_back(half[i]);
            }
            full.push_back(half.back());
            for (int i = (int)half.size() - 2; i >= 0; i--) {
                full.push_back(half[i]);
            }
        }
        
        // Build frequency vector of digits 0..9.
        array<int, 10> freq = {0};
        for (int d : full) {
            freq[d]++;
        }
        freqSet.insert(freq);
    }
    
    // DFS recursively chooses digits for the "half" of the palindrome.
    // pos: current position in the half (0-indexed).
    // current_mod: current accumulated modulo value from contributions.
    // half: the chosen digits so far.
    void dfs(int pos, int current_mod, int n, int k, vector<int>& half) {
        if (pos == L) {
            // Once the half is complete, the full palindrome is implicitly determined.
            // Check if the current modulo state (over contributions) is 0.
            if (current_mod % k == 0) {
                processFullNumber(half, n);
            }
            return;
        }
        
        int start_digit = 0, end_digit = 9;
        vector<int> digitChoices;
        if (pos == 0) {  
            // First digit of the full number may not be zero.
            start_digit = 1;
            // For some k (like k == 5) a divisibility rule could force the last digit.
            // Since the first and last digits are equal, if k==5 only digit 5 is allowed.
            if (k == 5)
                digitChoices.push_back(5);
            else {
                for (int d = start_digit; d <= end_digit; d++) {
                    digitChoices.push_back(d);
                }
            }
        } else {
            for (int d = start_digit; d <= end_digit; d++) {
                digitChoices.push_back(d);
            }
        }
        
        for (int d : digitChoices) {
            // Update the modulo state using the precomputed contribution of the current position.
            int new_mod = (current_mod + (d * contribution[pos]) % k) % k;
            half.push_back(d);
            dfs(pos + 1, new_mod, n, k, half);
            half.pop_back();
        }
    }
    
    long long countGoodIntegers(int n, int k) {
        // Initialize parameters.
        N = n, K = k;
        initFactorials();
        
        // Precompute powers of 10 modulo k for positions 0..n-1.
        pow10_mod.resize(n);
        pow10_mod[0] = 1 % k;
        for (int i = 1; i < n; i++) {
            pow10_mod[i] = (1LL * pow10_mod[i - 1] * 10LL) % k;
        }
        
        // Number of digits that fully determine the palindrome.
        L = (n + 1) / 2;
        contribution.resize(L);
        
        // Precompute contributions.
        // For even n, digit at position p contributes from positions p and (n-1-p).
        // For odd n, the middle digit contributes only once.
        if(n % 2 == 0) {
            for (int p = 0; p < L; p++) {
                contribution[p] = (pow10_mod[n - 1 - p] + pow10_mod[p]) % k;
            }
        } else {
            for (int p = 0; p < L - 1; p++) {
                contribution[p] = (pow10_mod[n - 1 - p] + pow10_mod[p]) % k;
            }
            contribution[L - 1] = pow10_mod[n / 2] % k;
        }
        
        // Use DFS to generate all valid half digit sequences.
        vector<int> half;
        dfs(0, 0, n, k, half);
        
        // For each unique frequency vector, count how many n-digit numbers have that frequency.
        long long answer = 0;
        for (auto freq : freqSet) {
            // Total arrangements = n! / (f0! * f1! * ... * f9!)
            long long total = fact[n];
            for (int d = 0; d < 10; d++) {
                total /= fact[freq[d]];
            }
            
            // Count arrangements with a leading zero to subtract them.
            long long bad = 0;
            if (freq[0] > 0) {
                long long totBad = fact[n - 1];
                totBad /= fact[freq[0] - 1];
                for (int d = 1; d < 10; d++) {
                    totBad /= fact[freq[d]];
                }
                bad = totBad;
            }
            
            answer += (total - bad);
        }
        return answer;
    }
};

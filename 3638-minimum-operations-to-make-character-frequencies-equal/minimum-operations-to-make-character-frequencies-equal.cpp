class Solution {
public:
    int makeStringGood(string s) {
        int freq[26] = {};
        int m = 0;
        for(const char c: s) {
            freq[c-'a']++;
            m = max(m, freq[c-'a']); // maximum frequenccy
        }
        int best = s.size();
        for(int i = m; i >= 0; i--) {
            int result = operations(freq, i);
            best = min(best, result);
        }
        return best;
    }
    int operations(int* freq, int k) {
        int prev_carry = 0;
        int prev_nocarry = 0;
        int carry = 0;
        for(size_t i = 0; i < 26; i++) {
            if(freq[i] >= k) {
                // if we are already larger than k, then the incoming carry does not matter
                carry = freq[i] - k;
                // both results are the same
                prev_carry = freq[i] - k + min(prev_carry, prev_nocarry); 
                prev_nocarry = prev_carry; 
            } else {
                if(freq[i] + carry >= k) {
                    int prev = prev_nocarry;
                    // either we accept the carry or we have to fill in the gap upwards
                    prev_nocarry = min(prev_carry, k - freq[i] + prev_nocarry);  
                    // to get a carry we always decrease and ignore the incoming carry
                    prev_carry = freq[i] + min(prev_carry, prev);
                    carry = freq[i];
                } else {
                    int prev = prev_carry;
                    // to get a carry we always decrease and ignore the incoming carry
                    prev_carry = freq[i] + min(prev_carry, prev_nocarry); 
                    // for the no carry option we increase up until k using the cary or not
                    prev_nocarry = min(k - (freq[i] + carry) + prev, k - freq[i] + prev_nocarry);
                    carry = freq[i]; 
                }
                
            }
        }
        return min(prev_carry, prev_nocarry); 
    }
};
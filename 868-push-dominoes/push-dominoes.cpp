class Solution {
public:
    string pushDominoes(string s) {
        int n = s.size();
        int prev = -1;
        char prevForce = 'L';
        
        for (int i = 0; i <= n; ++i) {
            char currForce = (i < n ? s[i] : 'R');
            if (currForce == '.') continue;
                        if (prevForce == currForce) {
                for (int k = prev + 1; k < i; ++k) {
                    s[k] = currForce;
                }
            } 
            else if (prevForce == 'R' && currForce == 'L') {
                int left = prev + 1, right = i - 1;
                while (left < right) {
                    s[left++] = 'R';
                    s[right--] = 'L';
                }
            }
            prev = i;
            prevForce = currForce;
        }
        
        return s;
    }
};

#include <iostream>

class Solution {
public:
    bool canMakeSubsequence(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        int cp = 0;
        bool found;
        for(int i =0;i<m;i++){
            found = false;
            for(int j = cp; j<n;j++){
                if(str2[i] == str1[j] || ((str1[j] - 'a' + 1) % 26 + 'a')==str2[i]){
                    cp = j+1;
                    found = true;
                    break;
                }
            }
            if(!found){
                return false;
            }
        }
        return found;
    }
};
#include <iostream>
#include <string>
class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        int k = spaces.size();
        int m;
        std::string rt(&s[0], spaces[0]);
        std::string temp;
        char* itr = &s[0];
        itr+=spaces[0];
        for (const int* ptr = &spaces[1]; ptr < &spaces[k]; ++ptr) {
            m = *ptr - *(ptr - 1);
            std::string temp(itr, m);
            itr+=m;
            rt += " "+temp;
        }
        std::string substring(itr);
        rt += " "+ substring;
        return rt;
    }
};
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
    std::istringstream stream(sentence);  // Create a stream from the input string
    std::vector<std::string> words;   // Vector to hold the words
    std::string word;
    int k = searchWord.size();
    int i = 0;
    while (stream >> word) {          // Read each word separated by whitespace
       i++;
       if(word.size()<k){
        continue;
       }
       if(word.substr(0, k) == searchWord){
        return i;
       }
    }
    return -1;
    }
};
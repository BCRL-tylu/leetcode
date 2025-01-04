class Solution {
public:
    int countPalindromicSubsequence(string s) {
    std::vector<std::vector<int>> matrix(26, std::vector<int>(26, 0));
    std::vector<int> value(26, 0);
    std::vector<bool> visited(26, false);
    std::vector<int> ans_value(26, 0);
    int ans = 0;

    for (char c : s) {
        int current = c - 'a';
        
        bool fm = false;
        // Step (1): Update the matrix and value for all visited letters
        for (int i = 0; i < 26; ++i) {
            if (visited[i]) {
                if (matrix[i][current] == 0) {
                    matrix[i][current] = 1;
                    if(current == i){
                        fm = true;
                    }
                    if(value[i] == 26){
                        break;
                    }
                    value[i]++;
                }
            }
        }

        // Step (2): Mark the letter as visited if it's met for the first time
        if (!visited[current]) {
            visited[current] = true;
        } else {
            // Step (3): If the letter is already visited and not adjacent to an identical char
                ans_value[current] =value[current];
                if(fm){ ans_value[current]--;}
        }
    }

    for(int i =0; i<26;i++){
        ans += ans_value[i];
    }

    return ans;
    }
};
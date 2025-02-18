class Solution {
private:
    int dfs(vector<int>& letter) {
        int count = 0;
        for(int i = 0; i < 26; i++) {
            if(letter[i] == 0) continue;
            letter[i]--; // Use the letter
            count += 1 + dfs(letter); // Count this sequence and recurse
            letter[i]++; // Backtrack
        }
        return count;
    }

public:
    int numTilePossibilities(string tiles) {
        vector<int> letter(26, 0);
        for(char c : tiles) letter[c - 'A']++; // Count frequency of each letter
        return dfs(letter);
    }
};
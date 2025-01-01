class Solution {
public:
    string answerString(string word, int numFriends) {
        char maxm = 'a';
        int n = word.size();
        if (numFriends == 1) return word;

        int k = n - numFriends + 1;
        string ans = "";

        // Find the maximum character in the word
        for (char c : word) {
            maxm = max(maxm, c);
        }

        string maxstring = "";  // To keep track of the largest substring
        int start_index = 0;    // To track the starting index of the max substring

        // Traverse the string to find substrings starting with maxm
        for (int i = 0; i < n; i++) {
            if (word[i] == maxm) {
                string temp_ans = "";
                temp_ans += maxm;

                // Collect characters while the conditions hold
                while (i + 1 < n && temp_ans.size() < min(k, n - i) && (word[i + 1] != maxm || temp_ans.back() == maxm)) {
                    temp_ans += word[++i];
                }

                // Compare temp_ans with current largest substring
                if (temp_ans > maxstring) {
                    maxstring = temp_ans; // Update the largest substring
                    start_index = i;      // Update the index of the largest substring
                }
            }
        }

        // Build the answer based on the largest substring found
        int sz = maxstring.size();
        string temp_add = word.substr(start_index + 1, min(k - sz, n - start_index));

        ans = maxstring + temp_add; // Combine the largest substring with the additional characters

        return ans.substr(0, k); // Return the result trimmed to size k
    }
};

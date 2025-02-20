struct TrieNode {
    TrieNode* left = nullptr;  // Represents '0'
    TrieNode* right = nullptr; // Represents '1'
    bool isEnd = false;        // Marks end of a valid string
};

class Solution {
private:
    bool backtrack(TrieNode* node, string& s, int n) {
        if (s.size() == n) {
            return !node->isEnd;
        }
        if (!node->left) { s.push_back('0'); return true;}
        s.push_back('0');
        if (backtrack(node->left, s, n)) return true;
        s.pop_back(); // Undo

        if (!node->right) {s.push_back('1'); return true;}
        s.push_back('1');
        if (backtrack(node->right, s, n)) return true;
        s.pop_back(); // Undo
        return false;
    }

public:
    string findDifferentBinaryString(vector<string>& nums) {
        TrieNode* root = new TrieNode();
        int n = nums[0].size();
        for (auto s : nums) {
            TrieNode* node = root;
            for (char c : s) {
                if (c == '0') {
                    if (!node->left) node->left = new TrieNode();
                    node = node->left;
                } else { // c == '1'
                    if (!node->right) node->right = new TrieNode();
                    node = node->right;
                }
            }
            node->isEnd = true;
        }
        string s;
        backtrack(root, s, n);
        while(s.size()<n){
            s.push_back('0');
        }
        return s;
    }
};

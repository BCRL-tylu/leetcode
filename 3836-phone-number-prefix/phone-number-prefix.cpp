struct TrieNode {
    TrieNode* c[10] = {nullptr};
    bool isEnd = false;
};
class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
};

class Solution {
public:
    bool phonePrefix(vector<string>& numbers) {
        Trie trie;
        for (int i = 0; i < numbers.size(); i++) {
            TrieNode* n = trie.root;
            for (char d : numbers[i]) {
                int ind = d-'0';
                if(n->isEnd) return false; 
                if (!n->c[ind]) n->c[ind] = new TrieNode();
                n = n->c[ind];
            }
            if(n->isEnd) return false;
            for (int i = 0; i < 10; i++) if (n->c[i]) return false;
            n->isEnd = true;
        }
        return true;
    }
};
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
        for (const string& num : numbers) {
            TrieNode* node = trie.root;
            for (char d : num) {
                int index = d - '0';
                if (node->isEnd) return false;
                if (!node->c[index]) node->c[index] = new TrieNode();
                node = node->c[index];
            }
            if (node->isEnd) return false;
            if (has(node)) return false;
            node->isEnd = true;
        }
        return true;
    }

private:
    bool has(TrieNode* node) {
        for (int i = 0; i < 10; i++) if (node->c[i]) return true;
        return false;
    }
};

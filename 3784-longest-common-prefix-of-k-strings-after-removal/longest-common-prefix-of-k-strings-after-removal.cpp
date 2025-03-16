class Solution {
public:
    struct Node {
        unordered_map<char, Node*> ch;
        int cnt = 0, d = 0, dp = 0;
    };
    
    struct Trie {
        Node* r;
        int k;
        Trie(int kk): k(kk) { r = new Node(); r->d = 0; }
        
        void ins(const string &s) {
            Node* cur = r;
            cur->cnt++;
            for (char c : s) {
                if (!cur->ch.count(c)) {
                    Node* nxt = new Node();
                    nxt->d = cur->d + 1;
                    cur->ch[c] = nxt;
                }
                cur = cur->ch[c];
                cur->cnt++;
            }
        }
        
        void dfs(Node* cur) {
            cur->dp = (cur->cnt >= k ? cur->d : 0);
            for (auto &p : cur->ch) {
                dfs(p.second);
                cur->dp = max(cur->dp, p.second->dp);
            }
        }
        
        void updPath(const vector<Node*>& path) {
            for (int i = path.size() - 1; i >= 0; i--) {
                int nd = (path[i]->cnt >= k ? path[i]->d : 0);
                for (auto &p : path[i]->ch)
                    nd = max(nd, p.second->dp);
                path[i]->dp = nd;
            }
        }
        
        void updWord(const string &s, int delta) {
            vector<Node*> path;
            Node* cur = r;
            path.push_back(cur);
            for (char c : s) {
                cur = cur->ch[c];
                path.push_back(cur);
            }
            for (auto node : path)
                node->cnt += delta;
            updPath(path);
        }
    };
    
    vector<int> longestCommonPrefix(vector<string>& w, int k) {
        vector<string> v = w;
        Trie t(k);
        for (auto &s : v)
            t.ins(s);
        t.dfs(t.r);
        vector<int> ans;
        for (auto &s : v) {
            t.updWord(s, -1);
            ans.push_back(t.r->cnt < k ? 0 : t.r->dp);
            t.updWord(s, 1);
        }
        return ans;
    }
};

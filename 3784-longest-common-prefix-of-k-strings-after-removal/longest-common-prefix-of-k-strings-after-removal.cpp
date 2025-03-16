
class Solution {
    // compute the pairwise longest common prefix
    int helper(string& a, string& b) {
        int res = 0;
        for(; res < a.length() && res < b.length() && a[res] == b[res]; res++) {}
        return res;
    }
    // Sliding Window over Sorted Order to Find the Best k-Group
    pair<vector<int>,int> helper(vector<string>& S, vector<int>& ord, int k) {
        vector<int> best{0,0};
        int bestIndex = -1;
        for(int i = k - 1; i < S.size(); i++) {
            int j = i - k + 1;
            int ii = ord[i], jj = ord[j];

            if(min(S[ii].length(), S[jj].length()) <= best[1]) continue;
            int match = helper(S[ii], S[jj]), now = match;
            if(match <= best[1]) continue;
            if(match > best[0]) swap(match, best[0]);
            if(match > best[1]) swap(match, best[1]);
            if(best[0] == now) bestIndex = i;
        }

        return {best, bestIndex};
    }
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        if(words.size() <= k) return vector<int>(words.size());
        vector<int> ord(words.size());
        for(int i = 0; i < words.size(); i++) ord[i] = i;
        sort(begin(ord), end(ord), [&](int i, int j) {return words[i] < words[j];});
        vector<int> rord(words.size());
        for(int i = 0; i < words.size(); i++) rord[ord[i]] = i;
        auto [best, bestIndex] = helper(words,ord,k);
        vector<int> res;
        for(int i = 0; auto& w : words) {
            if(w.length() < best[0]) res.push_back(best[0]);
            else if(best[0] == best[1]) res.push_back(best[0]);
            else {
                if(bestIndex - k + 1 <= rord[i] and rord[i] <= bestIndex) res.push_back(best[1]);
                else res.push_back(best[0]);
            }
            i++;
        }
        return res;
    }
};
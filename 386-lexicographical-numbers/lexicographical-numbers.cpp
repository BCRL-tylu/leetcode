class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> ans;
        int i = 1;
        ans.push_back(i);
        while (i * 10 <= n) {
            i *= 10;
            ans.push_back(i);
        }

        for (int cnt = ans.size(); cnt < n;) {
            // 1) try to go deeper (append a '0')
            if (i * 10 <= n) {
                i *= 10;
            }
            else {
                // 2) else try to go to next sibling
                if (i % 10 != 9 && i + 1 <= n) {
                    ++i;
                }
                else {
                    // 3) else back off until we can increment
                    while (i % 10 == 9 || i + 1 > n) {
                        i /= 10;
                    }
                    ++i;
                }
            }
            ans.push_back(i);
            ++cnt;
        }


        return ans;
    }
};

class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.size();
        int l1 = 0, r1 = 0, count = 0;
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            if (boxes[i] == '1') {
                count += i;
                r1++;
            }
        }
        if (boxes[0] == '1') {
            l1++;
            r1--;
        }
        ans[0] = count;

        for (int i = 1; i < n; i++) {
            count = count + l1 - r1;
            ans[i] = count;
            if (boxes[i] == '1') {
                l1++;
                r1--;
            }
        }
        return ans;
    }
};
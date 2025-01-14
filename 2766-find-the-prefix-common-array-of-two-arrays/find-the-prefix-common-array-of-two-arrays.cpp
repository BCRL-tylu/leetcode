class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int cc = 0 ,n=A.size();
        unordered_map<int,int> abrecord;
        vector<int> ans(n);
        for(int i = 0;i<n;i++){
            cc+=(++abrecord[B[i]])/2+ (++abrecord[A[i]])/2;
            ans[i] = cc;
        }
        return ans;
    }
};
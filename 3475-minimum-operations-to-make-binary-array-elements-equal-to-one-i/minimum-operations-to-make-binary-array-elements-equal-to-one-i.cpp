class Solution {
public:
    int minOperations(vector<int>& nums) {
        vector<int> tn = nums;
        int n = nums.size(),count=0;
        for(int i =0;i<n-2;i++){
            if(tn[i]) continue;
            tn[i] = 1;
            tn[i+1] ^= 1;
            tn[i+2] ^= 1;
            count++;
        }
        return tn[n-1]&&tn[n-2]?count:-1;
    }
};
class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {

        int a = nums1.size(), b =nums2.size(),f=0,s=0;
        if(a%2) for(int i = 0;i<b;i++) f^=nums2[i];
        if(b%2) for(int i = 0;i<a;i++) s^=nums1[i];
        return f^s;
    }
};
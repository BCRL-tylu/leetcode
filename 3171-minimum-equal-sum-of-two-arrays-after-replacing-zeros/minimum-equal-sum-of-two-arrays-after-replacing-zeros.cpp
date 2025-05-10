class Solution {
public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        long long l1=0,l2=0,s1=0,s2=0;
        for(auto k:nums1) {
            if(!k) l1++;
            s1+=(long long)k;
        }
        for(auto k:nums2) {
            if(!k) l2++;
            s2+=(long long)k;
        }
        long long k1 =s1+l1,k2=s2+l2;
        if(k1==k2) return k1; 
        if(k1>k2){
            if(l2!=0) return k1;
            else return -1;
        }else{
            if(l1!=0) return k2;
            else return -1;
        }
        return -1;
    }
};
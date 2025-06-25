class Solution {
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        int i1 = 0, i2 = 0;
        long long m = 10000000005LL;
        long long l, r, mid;
        while(i1 < nums1.size() && nums1[i1] < 0) ++i1;
        while(i2 < nums2.size() && nums2[i2] < 0) ++i2;
        vector<int> p1(nums1.begin()+i1, nums1.end()),
                    n1(nums1.begin(), nums1.begin()+i1),
                    p2(nums2.begin()+i2, nums2.end()),
                    n2(nums2.begin(), nums2.begin()+i2);
        // for(int a: p1) cout<<a<<' '; cout<<endl;
        // for(int a: n1) cout<<a<<' '; cout<<endl;
        // for(int a: p2) cout<<a<<' '; cout<<endl;
        // for(int a: n2) cout<<a<<' '; cout<<endl;
        if(k <= (long long)p1.size()*n2.size()+(long long)p2.size()*n1.size()){
            l = -m;
            r = 1;
            while(l < r){
                mid = (l+r)>>1;
                // cout<<format("l:{}, r:{}, mid:{}\n", l, r, mid);
                long long s = 0;
                for(int i = 0, j = 0; i < p1.size(); ++i){
                    while(j < n2.size() && (long long)p1[i] * n2[j] < mid) ++j;
                    s += j;
                    // cout<<format("s:{}, i:{}, j:{}\n", s, i, j);
                }
                for(int i = 0, j = 0; i < p2.size(); ++i){
                    while(j < n1.size() && (long long)p2[i] * n1[j] < mid) ++j;
                    s += j;
                    // cout<<format("s:{}, i:{}, j:{}\n", s, i, j);
                }
                if(s >= k) r = mid;
                else l = mid+1;
            }
        } else{
            k -= (long long)p1.size()*n2.size()+(long long)p2.size()*n1.size();
            // cout<<format("k:{}\n", k);
            l = 0;
            r = m;
            while(l < r){
                mid = (l+r)>>1;
                // cout<<format("l:{}, r:{}, mid:{}\n", l, r, mid);
                long long s = 0;
                for(int i = 0, j = (int)p2.size()-1; i < p1.size(); ++i){
                    while(j >= 0 && (long long)p1[i] * p2[j] >= mid) --j;
                    s += j+1;
                    // cout<<format("s:{}, i:{}, j:{}\n", s, i, j);
                }
                for(int i = 0, j = (int)n2.size()-1; i < n1.size(); ++i){
                    while(j >= 0 && (long long)n1[i] * n2[j] < mid) --j;
                    s += n2.size()-j-1;
                    // cout<<format("s:{}, i:{}, j:{}\n", s, i, j);
                }
                if(s >= k) r = mid;
                else l = mid+1;
            }
        }
        return l-1;
    }
};
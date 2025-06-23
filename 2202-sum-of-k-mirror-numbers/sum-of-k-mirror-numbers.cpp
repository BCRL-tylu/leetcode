class Solution {
private:
    bool kpal(long long k, long long a){
        vector<long long> u(100);
        long long pos =-1;
        while(a){
            pos++;
            u[pos] = a%k;
            a/=k;
        }
        for(long long i =0,j=pos;i<j;i++,j--){
            if(u[i]!=u[j]) return false;
        }
        return true;
    }
public:
    long long kMirror(int k, int n) {
        k = (long long)k;
        n = (long long)n;
        long long count=0;
        long long left =1;
        long long ans=0;
        while(count<n){
            long long right = left*10;
        for(long long o =0;o<2;o++){ //0 - odd,1-even
            for(long long i = left;i<right&&count<n;i++){
                    long long combine = i;
                    long long x = o == 0 ? i / 10 : i;
                    while(x){
                        combine*=10;
                        combine+=x%10;
                        x/=10;
                    }
                    if(kpal((long long)k,combine)){
                        count++;
                        ans+=combine;
                    }
                }
            }
            left = right;
        }
        return ans;
    }
};
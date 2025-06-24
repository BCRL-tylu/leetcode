class Solution {
public:
    vector<int> onceTwice(vector<int>& nums) {
        long long cnt[32]={};
        for(int v:nums){
            unsigned u=v;
            for(int i=0;i<32;i++) cnt[i]+=(u>>i)&1u;
        }
        unsigned diff=0;
        for(int i=0;i<32;i++) if(cnt[i]%3) diff|=1u<<i;
        unsigned key=diff&-diff;
        int cnta[32]={},cntb[32]={};
        for(int v:nums){
            unsigned u=v;
            if(u&key){
                for(int i=0;i<32;i++) cnta[i]+=(u>>i)&1u;
            } else {
                for(int i=0;i<32;i++) cntb[i]+=(u>>i)&1u;
            }
        }
        int vala=0,valb=0;
        for(int i=0;i<32;i++){
            if(cnta[i]%3) vala|=1u<<i;
            if(cntb[i]%3) valb|=1u<<i;
        }
        for(int i=0;i<32;i++){
            if(cnta[i]%3==1){
                return vector<int>{vala,valb};
            }else if(cnta[i]%3==2){
                return vector<int>{valb,vala};
            }
        }
        return {-1};
    }
};

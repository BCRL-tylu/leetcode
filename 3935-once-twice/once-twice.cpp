class Solution {
public:
    vector<int> onceTwice(vector<int>& nums) {
        int cnt[32]={};
        for(int v:nums){
            int u=v;
            for(int i=0;i<32;i++) cnt[i]+=(u>>i)&1;
        }
        int diff=0;
        for(int i=0;i<32;i++) if(cnt[i]%3) diff|=1<<i;
        int pivot=diff&-diff;
        int cnta[32]={},cntb[32]={};
        for(int v:nums){
            int u=v;
            if(u&pivot){
                for(int i=0;i<32;i++) cnta[i]+=(u>>i)&1;
            } else {
                for(int i=0;i<32;i++) cntb[i]+=(u>>i)&1;
            }
        }
        int vala=0,valb=0;
        for(int i=0;i<32;i++){
            if(cnta[i]%3) vala|=1<<i;
            if(cntb[i]%3) valb|=1<<i;
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

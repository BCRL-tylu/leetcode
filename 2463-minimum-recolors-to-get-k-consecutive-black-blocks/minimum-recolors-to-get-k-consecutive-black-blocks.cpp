class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int op = 0, n =blocks.size();
        for(int i =0;i<k;i++){
            if(blocks[i] =='W') op++;
        }
        if(k == n) return op;
        int ans=op;
        for(int i =1;i<=(int)blocks.size()-k;i++){
            if(blocks[i+k-1] =='W') op++;
            if(blocks[i-1] =='W') op--;
            ans=min(op,ans);
        }
        return ans;
    }
};
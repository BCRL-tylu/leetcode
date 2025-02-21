class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int r = accumulate(weights.begin(), weights.end(), 0),
        l = *max_element(weights.begin(), weights.end()),n=weights.size();
        while(l<r){
            int k = l+(r-l)/2, t =0, time =1;
            for(int i=0;i<n;i++){
                t+=weights[i];
                if(t>k){
                    time++;
                    t = weights[i];
                }
            }
            if(time<=days){
                r = k;
            }else{
                l = k+1;
            }
        }
        return r;
    }
};
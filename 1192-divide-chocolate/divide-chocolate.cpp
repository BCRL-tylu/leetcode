class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        // maximum we can get is sum sweetness/k
        int sum = accumulate(sweetness.begin(), sweetness.end(), 0);
        if(k==0) return sum;
        int r = sum/k, l=0, n = sweetness.size();
        
        while(l<r){
            int  m = l+(r-l)/2,cut =0, piece =0;
            for(int i =0; i<n;i++){
                cut+=sweetness[i];
                if(cut>=m){
                    cut = 0;
                    piece++;
                }
            }
            // at stop check whether number of pieces >= required (i.e >=k segments with size >=m)
            if(piece>=k+1){ // we have too small size
               l =m+1;
            }else{
                r =m;
            }
        }
        return l-1;
    }
};
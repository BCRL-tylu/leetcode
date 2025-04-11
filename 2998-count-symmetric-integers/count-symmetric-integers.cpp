class Solution {
public:
    bool issymmetric(int num,int d){
        int dh= d/2;
        int first = 0;
        int second = 0;
        for(int i = d-1;i>=0;i--){
            if(i>=dh){
                second+=(num%10);
            }
            else{
                first+=(num%10);
            }
            num = num/10;

        }
        return first == second;
    }
    int countSymmetricIntegers(int low, int high) {
        int cnt = 0;
        for(int i = low;i<=high;i++){
            int d = log10(i)+1;
            if(d%2!=0) continue;
            if(issymmetric(i,d)){
                cnt++;
                cout<<i<<" ";
            }
        }
        return cnt;
    }
};
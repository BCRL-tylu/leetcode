class Solution {
public:
    string intToRoman(int num) {
        string ans;
        string r = "MDCLXVI";
        vector<int> dig = {1000,100,10,1};
        int digit = 0;
        while (num != 0 && digit<4) {
            int temp = num/dig[digit];
            num -= temp*dig[digit];
            string toadd;
            int ss = digit*2;
            if(temp == 4){
                toadd+=r[ss];
                toadd+=r[ss-1];
            }else if(temp == 9){
                toadd+=r[ss];
                toadd+=r[ss-2];
            }else{
                if(temp>=5){
                    toadd+=r[ss-1];
                    for(int i =0; i<temp-5;i++) toadd+=r[ss];
                }else{
                    for(int i =0; i<temp;i++) toadd+=r[ss];
                }
            }
            ans+=toadd;
            digit++;
        }
        return ans;
    }
};
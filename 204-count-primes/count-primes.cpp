class Solution {
public:
    int countPrimes(int n) {
        int count=0;
        if(n<=1) return false;

        vector<bool>isPrime(n,true);
        isPrime[0]=false;
        if(n>1)isPrime[1]=false;

        for(int i=2;i*i<n;i++)
        {
            if(isPrime[i]==true){
                for(int j=i*i;j<n;j+=i)
                {
                    isPrime[j]=false;
                }
            }
        }

        for(bool i:isPrime)
        {
            if(i==true) {
                count++;
        }
        }
        return count;
        
    }
};
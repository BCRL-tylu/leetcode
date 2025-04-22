class Solution {
static const int MOD = 1e9+7;
private:
int add(int a, int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int mul(long long a, long long b){ return int((a*b) % MOD); }
int modpow(long long a, long long e=MOD-2){
    long long r=1;
    while(e){
        if(e&1) r=(r*a)%MOD;
        a=(a*a)%MOD;
        e>>=1;
    }
    return int(r);
}
public:
    int idealArrays(int n, int maxValue) {
    // 1) Precompute divisors < m for each m
    vector<vector<int>> divisors(maxValue+1);
    for(int d=1; d<=maxValue; ++d){
        // for each d, we put it in divisor[2d], divisor[3d].....
        for(int m=d*2; m<=maxValue; m+=d){
            divisors[m].push_back(d);
        }
    }

int L = 32 - __builtin_clz(maxValue);


    vector<vector<int>> f(L+1, vector<int>(maxValue+1, 0));
    for(int x=1; x<=maxValue; ++x)
        f[1][x] = 1;

    for(int l=2; l<=L; ++l){
        for(int x=1; x<=maxValue; ++x){
            long long sum = 0;
            for(int d: divisors[x]){
                sum += f[l-1][d];
                if(sum >= (long long)MOD) sum -= MOD;
            }
            f[l][x] = int(sum);
        }
    }

    vector<int> fact(n+1,1), invf(n+1,1);
    for(int i=1; i<=n; ++i)
        fact[i] = mul(fact[i-1], i);
    invf[n] = modpow(fact[n]);
    for(int i=n; i>0; --i)
        invf[i-1] = mul(invf[i], i);

    auto C = [&](int a, int b)->int{
        if(b<0 || b> a) return 0;
        return mul(fact[a], mul(invf[b], invf[a-b]));
    };

    int ans = 0;
    for(int x=1; x<=maxValue; ++x){
        long long ways = 0;
        for(int k=1; k<=L; ++k){
            int chains = f[k][x]; 
            int choose = C(n-1, k-1);    
            ways = (ways + 1LL * chains * choose) % MOD;
        }
        ans = add(ans, int(ways));
    }
    return ans;
    }
};
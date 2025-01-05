#define FOR(i,a,b)   for(int i = a; i < b.size(); ++i)
#define F(i,a,b)     for(int i = a; i < b; ++i)
#define F0(i,b)      for(int i = 0; i< b.size();++i)
#define BE(a)        a.begin(), a.end()
#define __S(a)       a.size()
#define pb(a)        push_back(a)
#define pr(a)        cout << a << " ";

typedef long long ll;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector <long long> vl;
typedef vector<vector<long long>> vvl;

class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        // can only be at the start or the end 
        // need to find the next number and the previous
        // bs
        sort(BE(coins));
        ll coinPre[100001]; // contain
        coinPre[0] = 0;
        F(i, 0, __S(coins)) 
            coinPre[i+1] = coinPre[i] + (ll)coins[i][2]*(coins[i][1]-coins[i][0]+1);

        ll ans = {};

        // need to,  find the upper bound the biggest [0] <= i
        auto up = [&](int i){
            int l = 0, r = __S(coins)-1;
            int biggest = -1;
            while (l <= r){
                int mid = (l+r)/2;
                if (coins[mid][0] <= i){
                    biggest = mid;
                    l = mid+1;
                }else{
                    r = mid-1;
                }
            }
            return biggest;
        };
        
        // need to find the lower bound ,find the smallest [1] >= i
        auto lw = [&](int i){
            int l = 0, r = __S(coins)-1;
            int biggest = -1;
            while (l <= r){
                int mid = (l+r)/2;
                if (coins[mid][1] >= i){
                    biggest = mid;
                    r = mid -1;
                }else{
                    l = mid +1;
                }
            }
            return biggest;
        };

        F0(i, coins){
            // from the start +k-1, find the previous one, the biggest [0] <= +k-1
            int pre = up(coins[i][0]+k-1);
            //cout << pre << " ";
            if (coins[i][0]+k-1 >= coins[pre][1]){
                ans = max(ans, coinPre[pre+1] - coinPre[i]);
            }else{
                //take partial
                ans = max(ans, coinPre[pre+1] - coinPre[i] - (ll)coins[pre][2]*(coins[pre][1] - (coins[i][0]+k-1)));
            }
            //cout << ans << endl;
            // from the end, -k+1, find the smallest [1] >= -k+1
            pre = lw(coins[i][1]-k+1);
            //cout << pre << " ";
            if (coins[i][1]-k+1 <= coins[pre][0]){
                ans = max(ans, coinPre[i+1] - coinPre[pre]);
            }else{
                //take partial
                ans = max(ans, coinPre[i+1] - coinPre[pre] - (ll)coins[pre][2]*((coins[i][1]-k+1)- coins[pre][0]));
            }
            //cout << ans << endl;
        }
        return ans;

        
    }
};
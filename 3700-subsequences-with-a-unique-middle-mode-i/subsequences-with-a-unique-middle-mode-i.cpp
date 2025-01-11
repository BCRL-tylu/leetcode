class Solution {
public:

#define ll long long
#define is ==
#define isnt !=

const ll cap = 1e3 + 10 ;

const ll mod = 1e9 +  7 ;

vector <ll> fac, invfac ;

    ll inv (ll a) {

        return a <= 1LL ? a : mod - (mod / a) * inv (mod % a) % mod ;

    }

    ll C (ll n, ll r) {

        if (r > n) return 0 ;

        return fac [n] * invfac [r] % mod * invfac [n - r] % mod ;

    }

    void Pcp () {
        
        fac.resize (cap + 1) ;

        invfac.resize (cap + 1) ;

        fac [0] = 1 ;

        for (ll i = 1 ; i <= cap ; i ++) fac [i] = fac [i - 1] * i % mod ;

        invfac [cap] = inv (fac [cap]) ;

        for (ll i = cap - 1 ; i >= 0 ; i --) invfac [i] = invfac [i + 1] * (i + 1) % mod ;

    }

    int subsequencesWithMiddleMode(vector<int>& nums) {

        Pcp () ;        

        set <ll> s ;

        map <ll, ll> mpg ;

        for (auto itr : nums) s.insert (itr) ;

        ll run = 1 ;

        for (auto itr : s) mpg [itr] = run, run ++ ;

        for (auto &itr : nums) itr = mpg [itr] ;

        vector <vector <ll>> pref (run, vector <ll> (nums.size (), 0)) ;

        for (int i = 1 ; i < run ; i ++) for (int j = 0 ; j < nums.size () ; j ++) pref [i][j] += (j ? pref [i][j - 1] : 0) + (nums [j] is i) ;

        ll n = nums.size () ;

        ll ans = 0 ;

        for (ll i = 2 ; i < n - 2 ; i ++) {

            ll l = pref [nums [i]][i - 1], r = pref [nums [i]][n - 1] - pref [nums [i]][i] ;

            // 2 2
            (ans += C (l, 2) * C (r, 2)) %= mod ;

            // 2 1
            (ans += C (l, 2) * C (r, 1) % mod * C (n - 1 - i - r, 1)) %= mod ;

            // 1 2
            (ans += C (l, 1) * C (i - l, 1) % mod * C (r, 2)) %= mod ;

            // 1 1
            (ans += C (l, 1) * C (i - l, 1) % mod * C (r, 1) % mod * C (n - 1 - i - r, 1)) %= mod ;

            // 2 0
            (ans += C (l, 2) * C (n - 1 - i - r, 2)) %= mod ;

            // 0 2
            (ans += C ((i - l), 2) * C (r, 2)) %= mod ;

            // 1 0
            ll t = n - 1 - i - r, v = 0, add = 0 ;

            for (int j = 1 ; j < run ; j ++) {

                if (j is nums [i]) continue ;

                ll c = pref [j][n - 1] - pref [j][i] ;

                (v += c * (t - c)) %= mod ;

            }

            (v *= inv (2)) %= mod ;

            for (int j = 1 ; j < run ; j ++) {

                if (j is nums [i]) continue ;
                
                ll c = pref [j][n - 1] - pref [j][i] ;

                ll ex = c * (t - c) % mod ;

                (add += pref [j][i - 1] * ((v - ex + mod) % mod)) %= mod ;

            }

            (add *= l) %= mod ;

            (ans += add) %= mod ;

            // 0 1
            t = i - l, v = 0, add = 0 ;

            for (int j = 1 ; j < run ; j ++) {

                if (j is nums [i]) continue ;

                ll c = pref [j][i - 1] ;

                (v += c * (t - c)) %= mod ;

            }

            (v *= inv (2)) %= mod ;

            for (int j = 1 ; j < run ; j ++) {

                if (j is nums [i]) continue ;

                ll c = pref [j][i - 1] ;

                ll ex = c * (t - c) % mod ;

                ll tot = pref [j][n - 1] - pref [j][i] ;

                (add += tot * ((v - ex + mod) % mod)) %= mod ;

            }

            (add *= r) %= mod ;

            (ans += add) %= mod ;

        }

        return ans ;
    }
};
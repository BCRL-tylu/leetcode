#include <vector>
using namespace std;

class ProductOfNumbers {
    vector<int> pd; // Prefix products
public:
    ProductOfNumbers() {
        pd.push_back(1); // Initialize with 1 to simplify multiplication
    }

    void add(int num) {
        if (num) {
            pd.push_back(pd.back() * num);
        } else {
            pd.clear();
            pd.push_back(1); // Reset prefix products
        }
    }

    const int MOD = 1e9 + 7;

    int modPow(int base, int exp, int mod) {
        long long res = 1;
        while (exp > 0) {
            if (exp & 1)
                res = res * base % mod;
            base = (long long)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

    int getProduct(int k) {
        return k < pd.size() ? (int)(1LL * pd.back() * modPow(pd[pd.size() - 1 - k], MOD - 2, MOD) % MOD) : 0;
    }
};

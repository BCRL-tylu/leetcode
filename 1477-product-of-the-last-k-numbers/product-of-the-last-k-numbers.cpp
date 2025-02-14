#include <vector>
using namespace std;

class ProductOfNumbers {
    vector<int> pd{1}; // Prefix products
public:
    ProductOfNumbers() {}

    void add(int num) {
        if (num) {
            pd.push_back(pd.back() * num);
        } else {
            pd.clear();
            pd.push_back(1); // Reset prefix products
        }
    }



    int getProduct(int k) {
        return k < pd.size() ? pd.back() / pd[pd.size() - k - 1] : 0;
        //return k < pd.size() ? (int)(1LL * pd.back() * modPow(pd[pd.size() - 1 - k], MOD - 2, MOD) % MOD) : 0;
    }
};

#include <vector>
using namespace std;

class ProductOfNumbers {
    vector<int> pd;  // Prefix products
public:
    ProductOfNumbers() {
        pd.push_back(1);  // Initialize with 1 to simplify multiplication
    }
    
    void add(int num) {
        if (num == 0) {
            pd.clear();  
            pd.push_back(1);  // Reset prefix products
        } else {
            pd.push_back(pd.back() * num);
        }
    }
    
    int getProduct(int k) {
        if ((int)pd.size() <= k) return 0;  // Fix out-of-bounds error
        return pd.back() / pd[pd.size() - 1 - k];  // Safe index access
    }
};

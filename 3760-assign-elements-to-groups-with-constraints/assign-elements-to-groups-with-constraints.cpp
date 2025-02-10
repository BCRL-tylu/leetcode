class Solution {
    const int MAXN = 1e5;
    vector<int> spf; // Smallest Prime Factor array

    void sieveSPF() {
        spf.resize(MAXN + 1);
        for (int i = 1; i <= MAXN; ++i)
            spf[i] = i;

        for (int i = 2; i * i <= MAXN; ++i) {
            if (spf[i] == i) { // i is prime
                for (int j = i * i; j <= MAXN; j += i) {
                    if (spf[j] == j)
                        spf[j] = i;
                }
            }
        }
    }

public:
    Solution() { sieveSPF(); } // Constructor to initialize SPF

    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        unordered_map<int, int> e_i; // element_index
        for (int i = 0; i < (int)elements.size(); i++) {
            if (!e_i.count(elements[i]))
                e_i[elements[i]] = i;
        }

        vector<int> ans;
        for (int j = 0; j < (int)groups.size(); j++) {
            int n = groups[j], m = INT_MAX;
            vector<pair<int, int>> primeFactors;
            
            while (n > 1) {
                int prime = spf[n], count = 0;
                while (n % prime == 0) {
                    n /= prime;
                    count++;
                }
                primeFactors.push_back({prime, count});
            }

            // Change product to long long to avoid overflow
            function<void(int, long long)> generateDivisors = [&](int index, long long product) {
                if (index == primeFactors.size()) {
                    if (e_i.count(product)) {
                        m = min(m, e_i[product]);
                    }
                    return;
                }
                int prime = primeFactors[index].first;
                int power = primeFactors[index].second;
                for (int i = 0; i <= power; ++i) {
                    generateDivisors(index + 1, product);
                    product *= prime; // No overflow as product is long long
                }
            };

            generateDivisors(0, 1);
            ans.push_back(m == INT_MAX ? -1 : m);
        }
        return ans;
    }
};

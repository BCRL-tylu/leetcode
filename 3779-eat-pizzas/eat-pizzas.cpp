class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        sort(pizzas.begin(),pizzas.end());
        long long n = pizzas.size(), ed = (n+4)/8, ans = 0, g = n/4-ed;
        for(int i = 0; i<ed;i++){
            ans+=pizzas[n-1-i];
        }

        for(int i = 0; i<g;i++){
            ans+=pizzas[n-2-ed-2*i];
        }
        return ans;
    }
};
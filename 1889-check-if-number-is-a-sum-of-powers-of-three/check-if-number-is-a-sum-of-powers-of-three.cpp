constexpr std::array<int, 16> g3() {
    std::array<int, 16> arr = {};
    arr[0] = 1;
    for (int i = 1; i <= 15; ++i) {
        arr[i] = arr[i - 1] * 3;
    }
    reverse(arr.begin(),arr.end());
    return arr;
}

constexpr array<int, 16> pot = g3();
class Solution {
public:
    bool checkPowersOfThree(int n) {
        for(auto v:pot){
            if(n<v) continue;
            n-=v;
        }
        return n==0;
    }
};
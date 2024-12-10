class Solution {
public:
std::vector<int> computeZArray(const string& s) {
    int n = s.size();
    vector<int> Z(n, 0);
    int l = 0, r = 0; // Window [l, r] with Z-box

    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            Z[i] = std::min(r - i + 1, Z[i - l]);
        }
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
            ++Z[i];
        }
        if (i + Z[i] - 1 > r) {
            l = i;
            r = i + Z[i] - 1;
        }
    }
    return Z;
}
int countg(const vector<int>& nums, int k) {
    int count = 0;
    for (int num : nums) {
        if (num >= k) {
            ++count;
        }
    }
    return count;
}
    int maximumLength(string s) {
        int n = s.size();
        char c = s[0]; 
        std::string cp(1, c); //current parttern
        string combined = cp + "$" + s;
        vector<int> z_ind = computeZArray(combined);
        int rt = countg(z_ind, cp.size());
        int rtsz = -1;
        if(rt>=3){
            rtsz = cp.size();
        }

        for(int i =1;i<n;i++){
            if(s[i]!=cp.back()){
                c = s[i]; 
                std::string temp(1, c); //current parttern
                cp = temp;
            }else{
                cp = cp+s[i];
            }
        int sz = cp.size();
        combined = cp + "$" + s;
        vector<int> z_ind = computeZArray(combined);
        int times = countg(z_ind, sz);
        if(times>=3){
            rtsz = max(rtsz,sz);
        }
        }
        return rtsz;
    }
};
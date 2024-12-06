class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        int sum =0;
        int last =1;
        int count = 0;
        while(sum<maxSum && last<=n && maxSum>=last){
            auto lf = std::find(banned.begin(), banned.end(), last);
            if(lf!=banned.end()){
                last++;
                banned.erase(lf);
                continue;
            }
            sum+=last++;
            count++;
        }
        if(sum>maxSum){
            return count-1;
        }
        return count;
    }
};
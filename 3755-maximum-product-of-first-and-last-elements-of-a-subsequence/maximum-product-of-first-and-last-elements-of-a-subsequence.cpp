class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        multiset<int> negr,posr;
        int n = nums.size();
        for(int i=m-1;i<n;i++){
            if(nums[i]>=0) posr.insert(nums[i]);
            else negr.insert(nums[i]);
        }
        long long ans=-1e10-1;
        for(int i=0;i<=n-m;i++){
            if(nums[i]>=0){
                if(!posr.empty()){
                    ans = max(ans,(long long)nums[i]* *posr.rbegin());
                }else if(!negr.empty()){
                    ans = max(ans,(long long)nums[i]* *negr.rbegin());
                }
            }else{
                if(!negr.empty()){
                    ans = max(ans,(long long)nums[i]* (*negr.begin()));
                }else if(!posr.empty()){
                    ans = max(ans,(long long)nums[i]* (*posr.begin()));
                }
            }
            int z = nums[i+m-1];
            if(z>=0){
                auto it = posr.find(z);
                posr.erase(it);
            }else{
                auto it = negr.find(z);
                negr.erase(it);
            } 
        }
        return ans==INT_MIN?-1:ans;
    }
};
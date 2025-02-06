class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int,int> hm;
        for(int i =0; i<(int)nums.size();i++){
            for(int j = i+1;j<(int)nums.size();j++){
                hm[nums[i]*nums[j]]++;
            }
        }
        int ans = 0;
        for(auto&[key, value]:hm){
            if(value<2)continue;
            ans+=value*(value-1);
        }
        return ans*4;
    }
};
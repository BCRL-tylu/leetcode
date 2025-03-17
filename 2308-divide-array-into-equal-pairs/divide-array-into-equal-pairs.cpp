class Solution {
public:
    bool divideArray(vector<int>& nums) {
        unordered_map<int,int> hm,ex;
        for(int i =0; i<nums.size();i++){
            hm[nums[i]] = ++hm[nums[i]]&1;
            if(hm[nums[i]]){
                ex[nums[i]] = false;
            }else{
                ex[nums[i]]  = true;
            }
        }
        for(auto pair:ex){
            if(pair.second){
                continue;
            }else{
                return false;
            }
        }
        return true;
    }
};
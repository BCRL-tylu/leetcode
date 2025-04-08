#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_map<int,int> freq,multi;
        for(auto nu:nums) if(++freq[nu]>1) multi[nu] = freq[nu]-1;
        int i =0,op=0;
        while(i<nums.size()){
            int temp = i;
            if(multi.size()==0){
                break;
            }
            while(i<temp+3 && i<nums.size()){
                if(--freq[nums[i]]==1){
                    multi.erase(nums[i]);
                }
                i++;
            }
            op++;
        }
        return op;
    }

};


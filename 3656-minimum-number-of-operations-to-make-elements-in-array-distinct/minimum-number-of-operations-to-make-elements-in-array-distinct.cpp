#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_map<int,int> freq,multi;
        for(auto nu:nums) if(++freq[nu]>1) multi[nu]=1;
        int i =0,op=0,n=nums.size();
        while(i<n){
            int temp = i+3;
            if(multi.size()==0) break;
            while(i<temp && i<n){
                if(--freq[nums[i]]==1) multi.erase(nums[i]);
                i++;
            }
            op++;
        }
        return op;
    }

};


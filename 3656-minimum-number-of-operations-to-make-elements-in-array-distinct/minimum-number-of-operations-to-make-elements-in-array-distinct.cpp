#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_map<int,int> freq;
        int i =0,op=0,n=nums.size(),multi=0;
        for(auto nu:nums) if(++freq[nu]>>1) multi++;
        while(i<n){
            int temp = i+3;
            if(multi==0) break;
            while(i<temp && i<n){
                if(--freq[nums[i]]) multi--;
                i++;
            }
            op++;
        }
        return op;
    }

};


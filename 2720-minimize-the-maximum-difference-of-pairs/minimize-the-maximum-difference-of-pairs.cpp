class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(),nums.end());
        int n=nums.size(),ma=0;
        vector<int> gaps(n-1);
        for(int i=0;i<n-1;i++){
            gaps[i]=abs(nums[i+1]-nums[i]);
            ma = max(ma,gaps[i]);
        }
        int l=0,r=ma;
        while(l<r){
            int mid = (r+l-1)/2,count=0;
            for(int i =0;i<n-1;i++){
                if(gaps[i]<=mid){
                    count++;
                    i++;
                }
            }
            if(count<p){ //not enougth count,increase number
                l=mid+1;
            }else{
                r=mid;
            }
        }
        return l;
    }
};
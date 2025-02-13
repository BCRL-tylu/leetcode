class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        int op =0;
        for(int i =0; i<(int)nums.size();i++){
            if(nums[i]>=k)continue;
            pq.push(nums[i]);
        }
        while(pq.size()>1){
            int x = pq.top();
            pq.pop();
            int y = pq.top();
            pq.pop();
            long long toadd = (long long)x*2+y;
            if(toadd<k){
                pq.push(toadd);
            }
            op++;
        }
        return op+pq.size();
    }
};
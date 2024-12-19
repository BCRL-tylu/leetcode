class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
         std::priority_queue<int> pq;
         int n = arr.size();
         int seg = 0;
         for(int i =0; i<n; i++){
            pq.push(arr[i]);
            int top = pq.top();
            if(top == i){
                pq.pop();
                seg++;
            }
         }
         return seg;
    }
};
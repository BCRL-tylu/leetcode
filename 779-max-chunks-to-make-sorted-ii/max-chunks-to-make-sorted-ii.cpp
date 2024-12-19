class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        std::vector<int> sortedArr = arr;
        std::sort(sortedArr.begin(), sortedArr.end());
        std::priority_queue<int> pq;
        std::priority_queue<int> temp_pq;
        int n = arr.size();
        int seg = 0;
        for (int i = 0; i < n; i++) {
            pq.push(arr[i]);
            temp_pq = pq;
            int ind = i;
            while (!temp_pq.empty()) {
                int top = temp_pq.top();
                if (top == sortedArr[ind]) {
                    temp_pq.pop();
                    ind--;
                }else{
                    break;
                }
            }
            if(temp_pq.empty()){
                pq = temp_pq;
                seg++;
            }
        }
        return seg;
    }
};
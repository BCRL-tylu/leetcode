class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        std::vector<int> sortedArr = arr;
        std::sort(sortedArr.begin(), sortedArr.end());
        int n = arr.size();
        int seg = 0;
        std::unordered_map<int, int> myMap;
        for (int i = 0; i < n; i++) {
            if(++myMap[sortedArr[i]]==0){
                myMap.erase(sortedArr[i]);
            }
            if(--myMap[arr[i]]==0){
                myMap.erase(arr[i]);
            }
            if(myMap.empty()){
                seg++;
            }
        }
        return seg;
    }
};
class Solution {
    private:
vector<int> findMaxToRight(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1); // Initialize result with -1
    int ma = arr[n-1];

    // Traverse the array from right to left
    for (int i = n - 2; i >= 0; --i) {
        ma = max(ma, arr[i+1]);
        result[i] =ma;
    }

    return result;
}

public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int n = values.size();
        vector<int> v_j;
        vector<int> v_i;
        for(int i=0;i<n;i++){
            v_j.push_back(values[i]-i);
            v_i.push_back(values[i]+i);
        }
        vector<int> v_j_max = findMaxToRight(v_j);
        int max_rt = INT_MIN;

        for(int i=0;i<n-1;i++){
           max_rt =max(max_rt,v_i[i]+v_j_max[i]);
        }
        return max_rt;

    }
};
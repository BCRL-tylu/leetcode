class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int n = nums.size(), count = 0;
        vector<pair<int, int>> m(n);
        for (int i = 0; i < n; i++)
            m[i] = {nums[i], i};
        sort(m.begin(), m.end());
        if(k == 1) return m[0].first;
        int l = m[0].first, r = m[n - 1].first, mid;
        while (l < r) {
            mid = (r + l - 1) >> 1;
            int vc = 0;
            for (int i = 0; m[i].first <= mid; i++) {
                vc++;
            }
            if (vc < k) { // not valid, not enought number smaller than mid to meet the capacity
                l = mid+1;
            } else {
                vector<int> length(n, 0);
                for (int i = 0; m[i].first <= mid; i++) 
                    length[m[i].second]=1;
                
                bool valid =false;
                length[1] = max(length[1],length[0]);
                for (int i = 2; i < n; i++) {
                    length[i] = max(length[i-2]+length[i],length[i-1]);
                    if(length[i]>=k){
                        valid = true;
                        break;
                    }
                }
                if (valid) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
        }
        return l;
    }
};
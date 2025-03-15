class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int l = *min_element(nums.begin(), nums.end());
        int r = *max_element(nums.begin(), nums.end());

        while (l < r) {
            int mid = (l + r) / 2;
            int count = k, prev_robbed = -2;
            bool  valid =false;
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] <= mid && i > prev_robbed + 1) {
                    count--;
                    prev_robbed = i;
                }
                if(count ==0){
                    valid=true;
                    break;
                }
            }

            if (valid) {
                r = mid;  // Try smaller capability
            } else {
                l = mid + 1;  // Increase capability
            }
        }
        return l;
    }
};

class Solution {
public:
    int maxScore(string s) {
        int n = s.size();
        vector<int> left(n,-1);
        vector<int> right(n,-1);
        int m = INT_MIN;

        int right_i = n-1;

        int left0 = s[0] - '0';
        int right1 = s[right_i] - '0';

        left[0] = left0  ^ 1;
        right[right_i] = right1;


        for(int i =1; i<n;i++){
            right_i --;

            left0 = s[i] - '0';
            right1 = s[right_i] - '0';

            left[i] = left[i-1] + (left0 ^ 1);
            right[right_i] = right[right_i+1] + right1;
            
            if(left[right_i]!=-1){
                m = max(m,right[right_i+1]+left[right_i]);
            }

            if(right[i]!=-1){
                m = max(m,right[i]+left[i-1]);
            }
        }
        return m;
    }
};
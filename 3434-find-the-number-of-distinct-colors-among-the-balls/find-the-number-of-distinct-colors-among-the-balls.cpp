class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int,int> c_i,i_c;
        vector<int> ans;
        int count = 0;
        for(auto& q:queries){
            int q0 = q[0], q1 = q[1];
            bool k =i_c.count(q0);
            int c = i_c[q0];
            if(k && c == q1){
                ans.push_back(count);
                continue;
            }
            if(!c_i.count(q1)) count++;
            c_i[q1]++;
            if(k & --c_i[c]==0){
                    c_i.erase(c);
                    count--;
            }
            i_c[q0] = q1;
            ans.push_back(count);
        }
        return ans;
    }
};
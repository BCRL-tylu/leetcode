class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int,int> c_i;
        unordered_map<int,int> i_c;
        vector<int> ans;
        int count = 0;
        for(auto& q:queries){
            if(i_c[q[0]] == q[1]){
                ans.push_back(count);
                continue;
            }
            if(c_i[q[1]]==0){
                count++;
            }
            c_i[q[1]]++;
            if(i_c.count(q[0])){
                c_i[i_c[q[0]]]--;
                if(c_i[i_c[q[0]]]==0) count--;
            }
            i_c[q[0]] = q[1];
            ans.push_back(count);
        }
        return ans;
    }
};
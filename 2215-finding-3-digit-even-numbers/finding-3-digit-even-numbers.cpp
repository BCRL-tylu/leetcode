class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        vector<int> d(10),ans;
        for(auto u:digits) d[u]++;

        for(int i=1;i<10;i++){
            vector<int> td = d;
            if(td[i]==0) continue;
            td[i]--;
            for(int j=0;j<10;j++){
                if(td[j]==0) continue;
                td[j]--;
                for(int k=0;k<10;k+=2){
                    if(td[k]==0) continue;
                    ans.push_back(100*i+10*j+k);
                }
                td[j]++;
            }
        }
        return ans;
    }
};
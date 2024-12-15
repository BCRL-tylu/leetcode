class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        std::set<std::pair<double, int>> mySet;
        double rt =0;
        for(int i=0; i<n;i++){
            vector<int> temp = classes[i];
            rt += double (temp[0])/temp[1];
            mySet.insert({double(temp[1]-temp[0])/(temp[1]+1)/temp[1],i});
        }
        int toadd = extraStudents;
        while(toadd--){
            auto maxp = mySet.rbegin();
            rt += maxp->first;
            int b = classes[maxp->second][1]++;
            pair<double, int> updated = {double(maxp->first)*b/(b+2),maxp->second};
            mySet.insert(updated);
            mySet.erase(--mySet.end());
        }
        return rt/n;
    }
};

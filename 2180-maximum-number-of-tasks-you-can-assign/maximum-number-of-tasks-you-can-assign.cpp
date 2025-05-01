class Solution {
private:
bool solve(int mid, multiset<int> w, vector<int> t, int pills, int strength){
    int i = 0, m = w.size(), n = t.size(), p = 0, j = t.size() - 1;
        for (int j = mid-1; j>=0; j--) {
            auto it = w.lower_bound(t[j]);
            if (it != w.end()) {
                int found = *it;
                w.erase(it);
                continue;
            }
            if (p < pills) {
                it = w.lower_bound(t[j] - strength);
                if (it != w.end()) {
                    int found = *it;
                    w.erase(it);
                    p++;
                    continue;
                }
            }
        }
        return (m-w.size())==mid;
}
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills,
                      int strength) {
        multiset<int> w;
        for (int i = 0; i < workers.size(); i++) {
            w.insert(workers[i]);
        }
        vector<int> t = tasks;
        sort(t.begin(), t.end());
        int l=0,r=min(w.size(),t.size());
        while(l<r){
            int mid = (l + r + 1) >> 1;
            if(solve(mid,w,t,pills,strength)){
                l=mid;
            }else{
                r=mid-1;
            }
        }
        return l;
    }
};
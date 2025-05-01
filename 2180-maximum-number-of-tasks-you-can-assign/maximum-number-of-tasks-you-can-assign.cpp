#include <bits/stdc++.h>
using namespace std;

class Solution {
    // Check if we can complete the k largest tasks using ≤ pills pills.
    bool canDo(int k,
               const vector<int>& t, 
               multiset<int>& workers, 
               int pills, 
               int strength) 
    {
        auto it_t = t.begin() + k;
        while (k--) {
            int task = *--it_t;
            
            auto it_w = prev(workers.end());
            if (*it_w >= task) {
                workers.erase(it_w);
                continue;
            }
            
            if (pills == 0) return false;
            int need = task - strength;
            it_w = workers.lower_bound(need);
            if (it_w == workers.end())
                return false;
            
            workers.erase(it_w);
            --pills;
        }
        return true;
    }
    
public:
    int maxTaskAssign(vector<int>& tasks,
                      vector<int>& workers,
                      int pills,
                      int strength) 
    {
        sort(tasks.begin(), tasks.end());
        multiset<int> W(workers.begin(), workers.end());
        
        int lo = 0, hi = min((int)tasks.size(), (int)workers.size()), ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            auto Wcopy = W; 
            if (canDo(mid, tasks, Wcopy, pills, strength)) {
                ans = mid; 
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};

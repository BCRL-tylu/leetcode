class Solution {
public:
    int findMinimumTime(vector<int>& strength) {
        int n = strength.size(); 
        int weight[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                weight[i][j] = (int)ceil((double)strength[j] / (i + 1)); 
            }
        }
        vector<int> y_sword(n, 0);
        vector<int> y_lock(n, 0); 
        vector<int> matched_lock(n, -1);
        vector<int> matched_sword(n, -1); 
        for (int sword = 0; sword < n; ++sword) {
            vector<int> min_slack(n, numeric_limits<int>::max());
            vector<int> slack_owner(n, -1); 
            vector<bool> visited_sword(n, false), visited_lock(n, false); 
            int current_sword = sword, current_lock = -1;
            while (true) {
                visited_sword[current_sword] = true; 
                int delta = numeric_limits<int>::max(), next_lock = -1;
                for (int lock = 0; lock < n; ++lock) {
                    if (!visited_lock[lock]) {
                        int cost = weight[current_sword][lock] - y_sword[current_sword] - y_lock[lock];
                        if (cost < min_slack[lock]) {
                            min_slack[lock] = cost; 
                            slack_owner[lock] = current_sword;
                        }
                        if (min_slack[lock] < delta) {
                            delta = min_slack[lock]; 
                            next_lock = lock;
                        }
                    }
                }
                for (int i = 0; i < n; ++i) {
                    if (visited_sword[i]) y_sword[i] += delta; 
                    if (visited_lock[i]) y_lock[i] -= delta;
                    else min_slack[i] -= delta;
                }
                current_lock = next_lock;
                visited_lock[current_lock] = true; 
                int sword_owner = slack_owner[current_lock];
                if (matched_sword[current_lock] == -1) {
                    while (current_lock != -1) {
                        int prev_lock = matched_lock[sword_owner];
                        matched_sword[current_lock] = sword_owner; 
                        matched_lock[sword_owner] = current_lock; 
                        current_lock = prev_lock; 
                        sword_owner = (current_lock != -1) ? slack_owner[current_lock] : -1; 
                    }
                    break;
                }
                current_sword = matched_sword[current_lock]; 
            }
        }
        int total_time = 0; 
        for (int i = 0; i < n; ++i) {
            total_time += weight[i][matched_lock[i]]; 
        }
        return total_time;
    }
};
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maxProfit(vector<int>& workers, vector<vector<int>>& tasks) {
        // Count workers by their skill.
        unordered_map<int, int> workerCount;
        for (int w : workers) {
            workerCount[w]++;
        }
        
        unordered_map<int, vector<int>> buckets;
        for (const auto& task : tasks) {
            int skill = task[0], profit = task[1];
            buckets[skill].push_back(profit);
        }
        
        long long totalProfit = 0;
        int extraCandidate = 0; 
        for (auto &entry : buckets) {
            int skill = entry.first;
            auto &profits = entry.second;
            if (workerCount.find(skill) == workerCount.end()) {
                int candidate = *max_element(profits.begin(), profits.end());
                extraCandidate = max(extraCandidate, candidate);
                continue;
            }
            
            int available = workerCount[skill];
            // If there are as many or fewer tasks than workers,
            // assign all tasks and leave nothing unassigned in this bucket.
            if ((int)profits.size() <= available) {
                for (int p : profits)
                    totalProfit += p;
            } else {
                nth_element(profits.begin(), profits.end() - available, profits.end());
                long long sumAssigned = 0;
                for (auto it = profits.end() - available; it != profits.end(); ++it) {
                    sumAssigned += *it;
                }
                totalProfit += sumAssigned;
                int candidate = *max_element(profits.begin(), profits.end() - available);
                extraCandidate = max(extraCandidate, candidate);
            }
        }
        
        totalProfit += extraCandidate;
        return totalProfit;
    }
};

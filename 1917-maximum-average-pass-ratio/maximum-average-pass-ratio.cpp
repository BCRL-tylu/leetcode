#include <vector>
#include <queue>
#include <utility>

class Solution {
public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        double totalRatio = 0;

        // Define a max heap with custom comparator
        auto cmp = [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
            return a.first < b.first; // Max heap based on the first element
        };
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(cmp)> maxHeap(cmp);

        for (int i = 0; i < n; i++) {
            int pass = classes[i][0];
            int total = classes[i][1];
            totalRatio += static_cast<double>(pass) / total;
            // Calculate the improvement and push it to the priority queue
            double improvement = static_cast<double>(total - pass) / (total + 1) / total;
            maxHeap.push({improvement, i});
        }

        while (extraStudents--) {
            auto maxp = maxHeap.top();
            maxHeap.pop();
            int idx = maxp.second;

            // Update the class size
            classes[idx][1]++;
            classes[idx][0]++;

            // Recalculate the improvement for the updated class
            double newImprovement = static_cast<double>(classes[idx][1] - classes[idx][0]) / (classes[idx][1] + 1) / classes[idx][1];
            maxHeap.push({newImprovement, idx});
            // Update the total ratio
            totalRatio += maxp.first; // Add the last improvement to the total ratio
        }

        return totalRatio / n;
    }
};

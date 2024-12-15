

class Solution {
public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        double rt = 0;
        // Define a max heap with custom comparator
        auto cmp = [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
            return a.first < b.first; // Max heap based on the first element
        };
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(cmp)> maxHeap(cmp);

        for (int i = 0; i < n; i++) {
            vector<int> temp = classes[i];
            rt += double(temp[0]) / temp[1];
            // Calculate the improvement and push it to the priority queue
            maxHeap.push({double(temp[1] - temp[0]) / (temp[1] + 1) / temp[1], i});
        }

        while (extraStudents--) {
            auto maxp = maxHeap.top();
            maxHeap.pop();
            rt += maxp.first;

            // Update the class size
            int b = classes[maxp.second][1]++;
            // Calculate the updated ratio and push it back to the priority queue
            maxHeap.push({double(maxp.first) * b / (b + 2), maxp.second});
        }

        return rt / n;
    }
};

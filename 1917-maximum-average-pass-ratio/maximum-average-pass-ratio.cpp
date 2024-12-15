
class Solution {
public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        double totalRatio = 0.0;

        // Priority queue to store the gain of adding an extra student (max-heap)
        auto gain = [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
            return a.first < b.first; // Max-heap: larger gain comes first
        };
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(gain)> pq(gain);

        // Calculate initial total ratio and populate priority queue
        for (int i = 0; i < n; ++i) {
            int pass = classes[i][0], total = classes[i][1];
            double currentRatio = double(pass) / total;
            double gainWithExtra = double(pass + 1) / (total + 1) - currentRatio;
            totalRatio += currentRatio;
            pq.emplace(gainWithExtra, i);
        }

        // Distribute extra students
        while (extraStudents--) {
            auto [maxGain, index] = pq.top();
            pq.pop();

            // Update the class with the extra student
            int& pass = classes[index][0];
            int& total = classes[index][1];
            pass++;
            total++;

            // Recalculate gain for the updated class
            double newRatio = double(pass) / total;
            double newGain = double(pass + 1) / (total + 1) - newRatio;

            // Update total ratio and push new gain to the priority queue
            totalRatio += maxGain;
            pq.emplace(newGain, index);
        }

        return totalRatio / n;
    }
};

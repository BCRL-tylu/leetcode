class Solution {
public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        // Function to find valid cuts for a given dimension
        auto canMakeCutsInDimension = [&](int index1, int index2) {
            vector<pair<int, int>> intervals;

            // Extract intervals from rectangles based on the specified indices
            for (const auto& rect : rectangles) {
                int start = rect[index1];
                int end = rect[index2];

                // Create an interval (start, end)
                if (start < end) {
                    intervals.emplace_back(start, end);
                }
            }

            // Sort intervals based on start
            sort(intervals.begin(), intervals.end());

            // Merge intervals and count the resulting segments
            vector<pair<int, int>> merged;
            for (const auto& interval : intervals) {
                if (merged.empty() || merged.back().second <= interval.first) {
                    // No overlap, add the new interval
                    merged.push_back(interval);
                } else {
                    // Overlap, merge with the last interval
                    merged.back().second = max(merged.back().second, interval.second);
                }
            }

            // Check if we have at least 3 non-overlapping intervals
            return merged.size() >= 3;
        };

        // Check for valid cuts in both dimensions (x: 0 and 2, y: 1 and 3)
        return canMakeCutsInDimension(0, 2) || canMakeCutsInDimension(1, 3);
    }
};
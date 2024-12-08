#include <vector>
#include <algorithm>
#include <utility> // For std::pair

using namespace std;

class Solution {
public:
    vector<int> generateMaxValues(const vector<vector<int>>& events) {
        int n = events.size();
        vector<int> maxValues(n);
        maxValues[n - 1] = events[n - 1][2];

        for (int i = n - 2; i >= 0; --i) {
            maxValues[i] = max(events[i + 1][2], maxValues[i + 1]);
        }
        return maxValues;
    }

    int maxTwoEvents(vector<vector<int>>& events) {
        int n = events.size();
        int maxdual = 0;
        int maxind = events[n - 1][2];

        // Step 1: Sort events based on the start times
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        // Step 2: Extract sorted first indices into a separate vector
        vector<int> sortedFirstIndices(n);
        for (int i = 0; i < n; ++i) {
            sortedFirstIndices[i] = events[i][0];
        }
        vector<int> maxValues = generateMaxValues(events);

        // Step 3: Process the events
        for (int i = 0; i < n - 1; i++) {
            // Update the maximum single event value
            if (events[i][2] > maxind) {
                maxind = events[i][2];
            }

            // Use binary search to find the next valid event
            int k = events[i][1];
            auto it = lower_bound(sortedFirstIndices.begin(), sortedFirstIndices.end(), k + 1);
            if (it != sortedFirstIndices.end()) {
                int startIndex = it - sortedFirstIndices.begin(); // Get the index of the found event
                int currentdual = maxValues[startIndex - 1];
                maxdual = max(maxdual, events[i][2] + currentdual);
            }
        }
        return max(maxdual, maxind);
    }
};

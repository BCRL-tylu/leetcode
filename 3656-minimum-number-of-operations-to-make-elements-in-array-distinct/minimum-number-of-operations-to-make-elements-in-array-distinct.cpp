#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int operations = 0;

        auto hasDistinctElements = [](const vector<int>& arr) {
            unordered_set<int> seen;
            for (int num : arr) {
                if (seen.find(num) != seen.end()) {
                    return false; // Found a duplicate
                }
                seen.insert(num);
            }
            return true; // All elements are distinct
        };

        while (!hasDistinctElements(nums)) {
            if (nums.size() >= 3) {
                nums.erase(nums.begin(), nums.begin() + 3); 
            } else {
                nums.clear();
            }
            operations++;
        }

        return operations;
    }
};


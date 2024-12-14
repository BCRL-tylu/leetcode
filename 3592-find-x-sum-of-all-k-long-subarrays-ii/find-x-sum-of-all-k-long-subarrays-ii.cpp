#define ll long long
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;
class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        unordered_map<ll, ll> freq; // Frequency map
        set<pair<ll, ll>> left, right; // Two sets to store pairs of (frequency, value)
        ll sum = 0;
        vector<ll> ans;
        // Add an element to the 'right' set and adjust the sum
        auto add_right = [&](ll count, ll value) {
            right.insert({count, value});
            sum += count * value;
            if (right.size() > x) {
                auto smallest = *right.begin(); // Get the smallest element
                sum -= smallest.first * smallest.second;
                left.insert(smallest);
                right.erase(right.begin());
            }
        };
        // Remove an element from the 'right' set and adjust the sum
        auto remove_right = [&](ll count, ll value) {
            auto current = make_pair(count, value);
            if (right.find(current) != right.end()) {
                sum -= count * value;
                right.erase(current);
                if (left.size() && right.size() < x) {
                    auto largest = *left.rbegin(); // Get the largest element from 'left'
                    sum += largest.first * largest.second;
                    right.insert(largest);
                    left.erase(largest);
                }
            } else {
                left.erase(current); // Erase from 'left' if it's not in 'right'
            }
        };
        int i = 0; // Sliding window start pointer
        for (int j = 0; j < n; j++) {
            if (freq[nums[j]] > 0) remove_right(freq[nums[j]], nums[j]);
            freq[nums[j]]++;
            add_right(freq[nums[j]], nums[j]);
            // Maintain the sliding window size of 'k'
            if (j - i + 1 > k) {
                remove_right(freq[nums[i]], nums[i]);
                freq[nums[i]]--;
                if (freq[nums[i]] > 0) {
                    add_right(freq[nums[i]], nums[i]);
                }
                i++;
            }
            // When window size reaches exactly 'k', record the sum
            if (j - i + 1 == k) ans.push_back(sum);
        }
        return ans;
    }
};
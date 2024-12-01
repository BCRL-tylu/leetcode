#include <deque>
#include <unordered_map>
#include <set>
#include <iostream>
#include <queue>
#include <algorithm>

class StatisticsTracker {
private:
    std::deque<int> numbers;                                   // To store numbers in insertion order.
    std::unordered_map<int, int> frequencyMap;                // To track frequency of numbers
    std::unordered_map<int, std::set<int>> freqMap;           // Maps frequencies to the corresponding numbers
    long long sum;                                            // Sum of all numbers
    int maxFrequency;                                         // Track maximum frequency
    std::multiset<int> left;                                 // Multiset for the lower half (max heap)
    std::multiset<int> right;                                // Multiset for the upper half (min heap)

    void balanceHeaps() {
        // Ensure the left heap has at most one more element than the right
        if (left.size() > right.size() + 1) {
            right.insert(*left.rbegin());  // Insert the largest from left to right
            left.erase(--left.end());       // Remove the largest from left
        } else if (right.size() > left.size()) {
            left.insert(*right.begin());    // Insert the smallest from right to left
            right.erase(right.begin());      // Remove the smallest from right
        }
    }

public:
    StatisticsTracker() : sum(0), maxFrequency(0) {}

    void addNumber(int number) {
        numbers.push_back(number);
        frequencyMap[number]++;
        int freq = frequencyMap[number];
        // Update the sum
        sum += number;
        // Update frequency map
        if (freq > 1) {
            // Remove the number from the previous frequency set
            freqMap[freq - 1].erase(number);
            if (freqMap[freq - 1].empty()) {
                freqMap.erase(freq - 1); // Clean up empty sets
            }
        }
        // Add the number to the current frequency set
        freqMap[freq].insert(number);
        // Update the maximum frequency
        maxFrequency = std::max(maxFrequency, freq);

        // Insert into the appropriate multiset
        if (left.empty() || number <= *left.rbegin()) {
            left.insert(number);
        } else {
            right.insert(number);
        }
        // Balance the heaps
        balanceHeaps();
    }

    void removeFirstAddedNumber() {
            int numberToRemove = numbers.front();
            numbers.pop_front(); // Remove the first element

            // Decrease the count in frequency map
            int freq = frequencyMap[numberToRemove];
            frequencyMap[numberToRemove]--;

            // Update the sum
            sum -= numberToRemove;

            // Update frequency map
            freqMap[freq].erase(numberToRemove);
            if (freqMap[freq].empty()) {
                freqMap.erase(freq); // Clean up empty sets
            }
            if (freq > 1) {
                freqMap[freq - 1].insert(numberToRemove);
            }

            // Update the maximum frequency if necessary
            if (freq == maxFrequency && freqMap.find(maxFrequency) == freqMap.end()) {
                maxFrequency--; // Decrease max frequency if it no longer exists
            }

            // Determine from which multiset to remove the number
            if (left.count(numberToRemove)) {
                left.erase(left.find(numberToRemove));
            } else {
                right.erase(right.find(numberToRemove));
            }
            // Rebalance the heaps after removal
            balanceHeaps();
    }

    int getMean() {
        return sum / numbers.size(); // Integer division gives the floored mean
    }

    int getMedian() {
        if (left.size() == right.size()) {
            return *right.begin(); // Return the larger median (top of right)
        } else {
            return *left.rbegin(); // Return the top of left
        }
    }

    int getMode() {
        return *freqMap[maxFrequency].begin(); // Smallest mode
    }
};

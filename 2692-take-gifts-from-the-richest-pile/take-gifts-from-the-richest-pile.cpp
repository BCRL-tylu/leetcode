#include <vector>
#include <set>
#include <cmath>

class Solution {
public:
    long long pickGifts(std::vector<int>& gifts, int k) {
        std::multiset<int> giftPiles(gifts.begin(), gifts.end());

        for (int i = 0; i < k; ++i) {
            // Get the largest pile
            auto it = giftPiles.end(); 
            --it; // Move to the last element (largest)
            int maxGifts = *it;

            // Calculate the remaining gifts after taking
            int remainingGifts = std::floor(std::sqrt(maxGifts));

            // Remove the largest pile and insert the remaining gifts
            giftPiles.erase(it);
            giftPiles.insert(remainingGifts);
        }

        // Calculate the total gifts remaining
        long long totalRemaining = 0;
        for (int giftsCount : giftPiles) {
            totalRemaining += giftsCount;
        }

        return totalRemaining;
    }
};

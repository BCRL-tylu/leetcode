class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        // Count the frequency of each character
        unordered_map<char, int> charCount;
        for (char c : s) {
            charCount[c]++;
        }

        // Create a max-heap (priority queue) sorted by character descending order
        priority_queue<pair<char, int>> pq;
        for (const auto& pair : charCount) {
            pq.push({pair.first, pair.second});
        }

        string result;
        pair<char, int> tempPair{' ', 0}; // Temporary pair to store excess characters

        while (!pq.empty() || tempPair.second > 0) {
            // Extract top character from the priority queue
            auto current = (tempPair.second > 0) ? tempPair : pq.top();
            if (tempPair.second == 0) pq.pop(); // Pop only when tempPair is empty

            // If the current character matches the last character, handle conflict
            if (!result.empty() && result.back() == current.first) {
                if (pq.empty()) break; // No alternative character to resolve conflict

                auto next = pq.top();
                pq.pop();

                // Append one character from the alternative
                result += next.first;
                next.second--;

                // Return the alternative back to the heap if still needed
                if (next.second > 0) {
                    pq.push(next);
                }
            } else {
                // Append as many characters as possible from the current character
                int pushCount = min(current.second, repeatLimit);
                result.append(pushCount, current.first);

                // Update remaining count
                current.second -= pushCount;
            }

            // Update the temporary pair for excess characters
            tempPair = (current.second > 0) ? current : pair<char, int>{' ', 0};
        }

        return result;
    }
};

class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        // Count the frequency of each character
        unordered_map<char, int> charCount;
        for (char c : s) {
            charCount[c]++;
        }

        // Create a max-heap (priority queue) based on character descending
        // order
        priority_queue<pair<char, int>> pq;
        for (const auto& pair : charCount) {
            pq.push({pair.first, pair.second});
        }

        string result;
        pair<char, int> tempPair{' ', 0}; // Initialize a temporary pair

        while (!pq.empty() || tempPair.second != 0) {
            // If the temporary pair has a valid character, handle it first
            if (tempPair.second != 0) {
                // If the current top character is the same as the last
                // character in the result, we break
                if (!result.empty() && result.back() == tempPair.first && pq.empty()) {
                    break;
                }
                if(!pq.empty()){
                auto current = pq.top();
                pq.pop();
                // Push as much as possible from the temporary pair
                result +=  current.first;
                current.second--;
                if(current.second!=0){
                    pq.push({current.first, current.second});
                }
                }
                int pushCount = min(tempPair.second, repeatLimit);
                for (int i = 0; i < pushCount; ++i) {
                    result += tempPair.first;
                }
                tempPair.second -=pushCount; // Decrease the remaining count in tempPair
            }else{ // when tempPair is empty
                auto current = pq.top();
                pq.pop();
                // If the current character is the same as the last character in
                // the result, we break
                if (!result.empty() && result.back() == current.first && pq.empty()) {break;}
                // Push as much as possible from current character
                int pushCount = min(current.second, repeatLimit);
                for (int i = 0; i < pushCount; ++i) {
                        result += current.first;
                }
                current.second -= pushCount; // Decrease count of current character
                if (current.second > 0) {
                    tempPair = {current.first,current.second};
                }
            }
        }
        return result;
    }
};
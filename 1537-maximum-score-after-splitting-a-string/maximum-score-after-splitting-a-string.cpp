class Solution {
public:
    int maxScore(string s) {
        int n = s.size();
        int leftCount = 0;  // Count of zeros on the left
        int rightCount = 0; // Count of ones on the right
        int maxScore = INT_MIN;

        // Calculate the initial count of ones in the entire string
        for (char c : s) {
            if (c == '1') rightCount++;
        }

        // Iterate through the string and calculate the score at each split
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == '0') leftCount++; // Add zero to leftCount
            else rightCount--;           // Remove one from rightCount

            // Update the maximum score
            maxScore = max(maxScore, leftCount + rightCount);
        }

        return maxScore;
    }
};

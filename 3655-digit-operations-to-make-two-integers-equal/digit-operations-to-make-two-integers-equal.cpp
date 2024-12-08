class Solution {
public:
// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// Function to generate all possible transformations by changing one digit
vector<int> getNeighbors(int n) {
    vector<int> neighbors;
    string s = to_string(n);
    for (int i = 0; i < s.size(); ++i) {
        char original = s[i];
        // Increment digit
        if (original != '9') {
            s[i] = original + 1;
            int neighbor = stoi(s);
            if (!isPrime(neighbor) && to_string(neighbor).length() == s.length()) {
                neighbors.push_back(neighbor);
            }
        }
        // Decrement digit
        if (original != '0') {
            s[i] = original - 1;
            int neighbor = stoi(s);
            if (!isPrime(neighbor) && to_string(neighbor).length() == s.length()) {
                neighbors.push_back(neighbor);
            }
        }
        s[i] = original; // Restore original digit
    }
    return neighbors;
}

    int minOperations(int n, int m) {
     if (isPrime(n) || isPrime(m)) return -1; // If either n or m is prime, return -1

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    unordered_set<int> visited;
    pq.push({n, n}); // {current_cost, current_number}
    visited.insert(n);

    while (!pq.empty()) {
        auto [currentCost, current] = pq.top();
        pq.pop();

        // If we reached the target number
        if (current == m) {
            return currentCost;
        }

        // Get neighbors (next states)
        for (int neighbor : getNeighbors(current)) {
            int newCost = currentCost + neighbor; // Add the neighbor value to the cost
            if (visited.find(neighbor) == visited.end() || newCost < currentCost) {
                visited.insert(neighbor);
                pq.push({newCost, neighbor}); // Push the new cumulative cost and neighbor
            }
        }
    }

    return -1; // If we exhaust all options without finding m
    }
};
class Solution {
public:
    int findMinimumTime(vector<int>& strength) {
        int n = strength.size(); // Let n be the number of swords (or locks).
        // Step 0: Construct weight matrix
        // Create a matrix where weight[i][j] represents the time it takes for sword i to break lock j.
        int weight[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Initialize the weight matrix C, where C_ij = ceiling(strength_j/sword damage_i)
                weight[i][j] = (int)ceil((double)strength[j] / (i + 1)); 
            }
        }

        // Hungarian algorithm variables
        // Dual potentials for swords and locks, initialized to 0.
        vector<int> y_sword(n, 0); //  y_v = 0 for each  v in P  (swords).
        vector<int> y_lock(n, 0); //  y_w = 0 for each  w in Q  (locks).
        
        // Matched pairs of swords and locks, initialized to -1 (unmatched).
        vector<int> matched_lock(n, -1); //  M(w) = -1  (unmatched lock for each sword).
        vector<int> matched_sword(n, -1); // M(v) = -1 (unmatched sword for each lock).

        // Main loop: Process each sword to find its optimal match
        for (int sword = 0; sword < n; ++sword) {
            vector<int> min_slack(n, numeric_limits<int>::max()); // Minimum slack values for each lock: delta_w = infty  for each  w in Q.
            vector<int> slack_owner(n, -1); // The sword responsible for each slack value.
            vector<bool> visited_sword(n, false), visited_lock(n, false); // Visited markers for swords and locks.

            int current_sword = sword, current_lock = -1; // Initialize current sword and lock.

            while (true) {
                // Mark the current sword as visited.
                visited_sword[current_sword] = true; 
                int delta = numeric_limits<int>::max(), next_lock = -1; // Initialize again delta = \infty and next lock.
                //  Update slack values and find the smallest slack
                for (int lock = 0; lock < n; ++lock) {
                    if (!visited_lock[lock]) {
                        // Calculate the cost for sword to lock assignment.
                        int cost = weight[current_sword][lock] - y_sword[current_sword] - y_lock[lock]; //  c_{vw} - y_v - y_w.
                        if (cost < min_slack[lock]) {
                            min_slack[lock] = cost; // Update the minimum slack delta_w for lock w.
                            slack_owner[lock] = current_sword; // Update the owner of slack.
                        }
                        if (min_slack[lock] < delta) {
                            delta = min_slack[lock]; // Update delta to the smallest slack.
                            next_lock = lock; // Update the next lock to visit.
                        }
                    }
                }
                //  Update dual variables to adjust for the smallest slack
                for (int i = 0; i < n; ++i) {
                    // Update dual variables based on visited status.
                    if (visited_sword[i]) y_sword[i] += delta; // y_v <- y_v + delta  for visited swords.
                    if (visited_lock[i]) y_lock[i] -= delta; // y_w <- y_w - delta for visited locks.
                    else min_slack[i] -= delta; // delta_w <- delta_w - delta for non-visited locks.
                }
                current_lock = next_lock; // Move to the next lock.
                visited_lock[current_lock] = true; // Mark the current lock as visited.
                int sword_owner = slack_owner[current_lock]; // Retrieve the sword that owns the slack.
                //  Augment the matching if an unmatched lock is found
                if (matched_sword[current_lock] == -1) {
                    while (current_lock != -1) {
                        int prev_lock = matched_lock[sword_owner]; // Previous lock matched to the sword.
                        matched_sword[current_lock] = sword_owner; // Augment the matching: M(w) = v.
                        matched_lock[sword_owner] = current_lock; // Augment the matching: M(v) = w .
                        current_lock = prev_lock; // Move to the previous lock.
                        sword_owner = (current_lock != -1) ? slack_owner[current_lock] : -1; // Get the sword owner for the previous lock.
                    }
                    break; // Exit the loop if an unmatched lock is found.
                }
                //  Move to the next sword in the alternating path
                current_sword = matched_sword[current_lock]; // Get the next sword from the current lock.
            }
        }
        //  Calculate the total minimum time from the optimal matching
        int total_time = 0; // Initialize the total time.
        for (int i = 0; i < n; ++i) {
            // Sum the weights of the matched pairs.
            total_time += weight[i][matched_lock[i]]; // Total time is the sum of costs c_vw for matched pairs.
        }
        return total_time; // Return the total minimum time.
    }
};
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        stack<TreeNode*> stk;
        int i = 0, n = traversal.size();

        while (i < n) {
            // Determine depth by counting dashes
            int depth = 0;
            while (i < n && traversal[i] == '-') {
                depth++;
                i++;
            }
            //  accumlate -
            
            // Read the node value
            int value = 0;
            while (i < n && isdigit(traversal[i])) {
                value = value * 10 + (traversal[i] - '0');
                i++;
            }
            // read number
            
            // Create the new node
            TreeNode* node = new TreeNode(value);
            
            // Maintain correct parent-child relationships
            // remove the attached nodes
            while (stk.size() > depth) { // when stack size > depth, that mean we can append at least 1 node to current node
                stk.pop();  // Move up to the correct parent level
            }
            
            if (!stk.empty()) {
                if (!stk.top()->left) // if left not occupied-attach to left
                    stk.top()->left = node;  // Attach as left child
                else 
                    stk.top()->right = node; // Attach as right child
            }
            
            stk.push(node);
        }
        while (stk.size() > 1) {
            stk.pop();
        }
        
        return stk.top();
    }
};

//| Step | Character | Depth | Node Value | Stack Contents |
//|------|----------|-------|------------|----------------|
//| 1    | `1`      | 0     | `1`        | `[1]` (root) |
//| 2    | `-2`     | 1     | `2`        | `[1, 2]` (2 is left child of 1) |
//| 3    | `--3`    | 2     | `3`        | `[1, 2, 3]` (3 is left child of 2) |
//| 4    | `---5`   | 3     | `5`        | `[1, 2, 3, 5]` (5 is left child of 3) |
//| 5    | `----8`  | 4     | `8`        | `[1, 2, 3, 5, 8]` (8 is left child of 5) |
//| 6    | `----9`  | 4     | `9`        | `[1, 2, 3, 5, 9]` (9 is right child of 5, pop 8) |
//| 7    | `--4`    | 2     | `4`        | `[1, 2, 4]` (4 is right child of 2, pop 3, 5, 9) |
//| 8    | `-6`     | 1     | `6`        | `[1, 6]` (6 is right child of 1, pop 2, 4) |
//| 9    | `---7`   | 3     | `7`        | `[1, 6, 7]` (7 is left child of 6) |
//| 10   | `--10`   | 2     | `10`       | `[1, 6, 10]` (10 is right child of 6, pop 7) |


//       1
//      / \
//     2   6
//    / \  / \
//   3   4 7 10
//  /
//  5
// / \
//8   9

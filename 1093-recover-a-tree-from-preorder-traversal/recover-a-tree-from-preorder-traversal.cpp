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
            //  accumlate - s
            
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
            while (stk.size() > depth) {
                stk.pop();  // Move up to the correct parent level
            }
            
            if (!stk.empty()) {
                if (!stk.top()->left) 
                    stk.top()->left = node;  // Attach as left child
                else 
                    stk.top()->right = node; // Attach as right child
            }
            
            stk.push(node);
        }
        
        // The root node is the bottom-most element in the stack
        while (stk.size() > 1) {
            stk.pop();
        }
        
        return stk.top();
    }
};

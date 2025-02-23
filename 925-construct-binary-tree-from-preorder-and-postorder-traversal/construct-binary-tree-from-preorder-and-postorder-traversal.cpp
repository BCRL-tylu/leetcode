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
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        stack<TreeNode*> stk;
        int i =0,j=0,n=preorder.size();

        while(i<n){
            int value = preorder[i];
            TreeNode* node = new TreeNode(value);

            if (!stk.empty()) {
                if (!stk.top()->left) 
                    stk.top()->left = node; 
                else 
                    stk.top()->right = node; 
            }
            stk.push(node);
            i++;
            while(stk.size()>1 && stk.top()->val == postorder[j]){
                stk.pop();
                j++;
            }
        }
        return stk.top();
    }
};
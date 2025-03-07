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
int length = INT_MIN;
private:
void dfs(TreeNode* node, int l, int par_v){
    if(node->val == par_v+1){
        l++;
    }else{
        l=1;
    }
    length = max(length,l);
    if(node->left){
        dfs(node->left,l,node->val);
    }
    if(node->right){
        dfs(node->right,l,node->val);
    }
    if(!node->left && !node->right) return;
}
public:
    int longestConsecutive(TreeNode* root) {
        dfs(root,1,root->val);
        return length;
    }
};
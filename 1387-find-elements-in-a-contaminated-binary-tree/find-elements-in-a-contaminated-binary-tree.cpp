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
class FindElements {
TreeNode* root;
public:
    FindElements(TreeNode* root) : root(root) {
        if(root->val == -1){
            root->val = 0;
            if(root->left!=nullptr){
                root->left->val = 1;
                FindElements(root->left);
            }
            if(root->right!=nullptr){
                root->right->val = 2;
                FindElements(root->right);
            }
        }else{
            if(root->left!=nullptr){
                root->left->val = (root->val<<1)+1;
                FindElements(root->left);
            }
            if(root->right!=nullptr){
                root->right->val = (root->val<<1)+2;
                FindElements(root->right);
            }
        }
    }
    
    bool find(int target) {
        TreeNode* obj = root;
        vector<bool> op; // 0 left-odd, 1 right-even
        while(target!=0){
            if(target%2){//odd
            (--target)>>=1;
            op.push_back(false);
            }else{
               target = (target-2)>>1;
            op.push_back(true); 
            }
        }
        for(int i = (int)op.size()-1;i>=0;i--){
            if(op[i]){
                if(obj->right == nullptr) return false;
                obj = obj->right;
            }else{
                if(obj->left == nullptr) return false;
                obj = obj->left;
            }// right
        }
        return true;
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
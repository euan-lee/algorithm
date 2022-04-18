class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == NULL)
            return 0;
        if(root->left == NULL && root->right == NULL)
            return 1;
        if(root->left != NULL && root->right == NULL)
            return maxDepth(root->left) + 1;
        if(root->right != NULL && root->left == NULL)
            return maxDepth(root->right) + 1;
        if(root->right != NULL && root->left != NULL) {
            int leftdepth = maxDepth(root->left);
            int rightdepth = maxDepth(root->right);
            return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
        }
    }
};

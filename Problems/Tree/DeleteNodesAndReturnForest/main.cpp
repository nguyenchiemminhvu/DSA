/**
https://leetcode.com/problems/delete-nodes-and-return-forest/description/

Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest. You may return the result in any order.

Example 1:

Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]

Example 2:

Input: root = [1,2,4,null,3], to_delete = [3]
Output: [[1,2,4]]
 
Constraints:

The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete)
    {
        std::unordered_set<int> deleteSet(to_delete.begin(), to_delete.end());
        std::vector<TreeNode*> res;
        removing(root, res, deleteSet, true);
        return res;
    }

private:
    TreeNode* removing(TreeNode* root, std::vector<TreeNode*>& res, std::unordered_set<int>& deleteSet, bool isRoot)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        bool deleted = (deleteSet.count(root->val) > 0);
        if (isRoot && !deleted)
        {
            res.push_back(root);
        }

        root->left = removing(root->left, res, deleteSet, deleted);
        root->right = removing(root->right, res, deleteSet, deleted);

        if (deleted)
            root = nullptr;

        return root;
    }
};

void traversal(TreeNode* root)
{
    if (root == nullptr)
    {
        return;
    }

    traversal(root->left);
    std::cout << root->val << " ";
    traversal(root->right);
}

int main()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    Solution sol;
    std::vector<int> to_delete = {3, 5};
    std::vector<TreeNode*> res = sol.delNodes(root, to_delete);

    for (TreeNode* t : res)
    {
        traversal(t);
        std::cout << endl;
    }

    return 0;
}
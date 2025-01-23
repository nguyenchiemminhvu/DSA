/**
https://leetcode.com/problems/closest-nodes-queries-in-a-binary-search-tree/description/

You are given the root of a binary search tree and an array queries of size n consisting of positive integers.

Find a 2D array answer of size n where answer[i] = [mini, maxi]:

mini is the largest value in the tree that is smaller than or equal to queries[i]. If a such value does not exist, add -1 instead.
maxi is the smallest value in the tree that is greater than or equal to queries[i]. If a such value does not exist, add -1 instead.
Return the array answer.

Example 1:

Input: root = [6,2,13,1,4,9,15,null,null,null,null,null,null,14], queries = [2,5,16]
Output: [[2,2],[4,6],[15,-1]]
Explanation: We answer the queries in the following way:
- The largest number that is smaller or equal than 2 in the tree is 2, and the smallest number that is greater or equal than 2 is still 2. So the answer for the first query is [2,2].
- The largest number that is smaller or equal than 5 in the tree is 4, and the smallest number that is greater or equal than 5 is 6. So the answer for the second query is [4,6].
- The largest number that is smaller or equal than 16 in the tree is 15, and the smallest number that is greater or equal than 16 does not exist. So the answer for the third query is [15,-1].

Example 2:

Input: root = [4,null,9], queries = [3]
Output: [[-1,4]]
Explanation: The largest number that is smaller or equal to 3 in the tree does not exist, and the smallest number that is greater or equal to 3 is 4. So the answer for the query is [-1,4].

Constraints:

The number of nodes in the tree is in the range [2, 105].
1 <= Node.val <= 106
n == queries.length
1 <= n <= 105
1 <= queries[i] <= 106
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries)
    {
        std::vector<int> inorderValues;
        inorderTraversal(root, inorderValues);

        std::vector<vector<int>> result;
        for (int query : queries)
        {
            int mini = -1;
            int maxi = -1;

            auto lower = lower_bound(inorderValues.begin(), inorderValues.end(), query);
            if (lower != inorderValues.begin())
            {
                mini = *(--lower);
                ++lower;
            }
            if (lower != inorderValues.end() && *lower == query)
            {
                mini = query;
            }

            if (lower != inorderValues.end())
            {
                maxi = *lower;
            }
            if (lower != inorderValues.end() && *lower == query)
            {
                maxi = query;
            }

            result.push_back({mini, maxi});
        }

        return result;
    }

private:
    void inorderTraversal(TreeNode* node, vector<int>& inorderValues)
    {
        if (!node)
            return;

        inorderTraversal(node->left, inorderValues);
        inorderValues.push_back(node->val);
        inorderTraversal(node->right, inorderValues);
    }
};

int main()
{
    Solution sol;
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(13);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(15);
    root->right->right->left = new TreeNode(14);

    std::vector<int> queries = {2, 5, 16};
    std::vector<std::vector<int>> res = sol.closestNodes(root, queries);
    for (const auto& pair : res)
    {
        std::cout << "[" << pair[0] << ", " << pair[1] << "] ";
    }
    std::cout << std::endl;
    return 0;
}
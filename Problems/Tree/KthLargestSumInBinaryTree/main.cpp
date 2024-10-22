/**
https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/

You are given the root of a binary tree and a positive integer k.

The level sum in the tree is the sum of the values of the nodes that are on the same level.

Return the kth largest level sum in the tree (not necessarily distinct). If there are fewer than k levels in the tree, return -1.

Note that two nodes are on the same level if they have the same distance from the root.

Input: root = [5,8,9,2,1,3,7,4,6], k = 2
Output: 13
Explanation: The level sums are the following:
- Level 1: 5.
- Level 2: 8 + 9 = 17.
- Level 3: 2 + 1 + 3 + 7 = 13.
- Level 4: 4 + 6 = 10.
The 2nd largest level sum is 13.

Constraints:

The number of nodes in the tree is n.
2 <= n <= 105
1 <= Node.val <= 106
1 <= k <= n
*/

#include <iostream>
#include <vector>
#include <queue>

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

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    using PQ = std::priority_queue<long long, std::vector<long long>, std::greater<long long>>;
    long long kthLargestLevelSum(TreeNode* root, int k)
    {
        PQ sum_level;
        BFS(root, sum_level, k);
        return sum_level.size() == k ? sum_level.top() : -1;
    }
private:
    void BFS(TreeNode* root, PQ& sum_level, int k)
    {
        std::queue<TreeNode*> q;
        q.push(root);

        int cur_level = 1;
        int next_level = 0;
        long long cur_sum = 0LL;
        while (!q.empty())
        {
            TreeNode* cur = q.front();
            q.pop();
            cur_level--;
            cur_sum += cur->val;

            if (cur->left != nullptr)
            {
                q.push(cur->left);
                next_level++;
            }

            if (cur->right != nullptr)
            {
                q.push(cur->right);
                next_level++;
            }

            if (cur_level == 0)
            {
                sum_level.push(cur_sum);
                if (sum_level.size() > k)
                {
                    sum_level.pop();
                }
                cur_sum = 0LL;
                cur_level = next_level;
                next_level = 0;
            }
        }
    }
};

int main()
{
    Solution sol;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    std::cout << sol.kthLargestLevelSum(root, 1) << std::endl;
    return 0;
}
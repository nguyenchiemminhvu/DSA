## Problem

https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/

```
Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property root.val = min(root.left.val, root.right.val) always holds.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:

Input: root = [2,2,5,null,null,5,7]
Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.

Example 2:

Input: root = [2,2,2]
Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.

Constraints:

The number of nodes in the tree is in the range [1, 25].
1 <= Node.val <= 231 - 1
root.val == min(root.left.val, root.right.val) for each internal node of the tree.
```

## Observations

1. **Special Tree Property**: This is a special binary tree where each internal node's value equals the minimum of its children: `root.val = min(root.left.val, root.right.val)`

2. **Root is Always Minimum**: Due to the tree property, the root will always contain the minimum value in the entire tree.

3. **Tree Structure**: Each node has either 0 children (leaf) or exactly 2 children (internal node).

4. **Finding Second Minimum**: We need to find the second smallest **distinct** value in the tree. If all values are the same, return -1.

5. **Key Insight**: Since the root is always the minimum, we need to find the smallest value that is greater than the root's value.

## Solution

### Approach: In-order Traversal with Set Collection

**Algorithm:**
1. Perform an in-order traversal of the binary tree
2. Collect all unique values in a set to automatically handle duplicates
3. Convert the set to a sorted list
4. Return the second element if it exists, otherwise return -1

**Time Complexity:** O(n log n) where n is the number of nodes
- O(n) for traversal
- O(n log n) for sorting the unique values

**Space Complexity:** O(n) for storing unique values and recursion stack

**Alternative Optimized Approach:**
Since we know the root contains the minimum value, we could optimize by:
1. Tracking only the second minimum during traversal
2. Avoiding the need to sort all values
3. This would reduce time complexity to O(n)

# Tags

Binary Tree, Tree Traversal, In-order Traversal, Set, Sorting


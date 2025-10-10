## Problem Description

https://leetcode.com/problems/find-duplicate-subtrees/description/

```
Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.

Example 1:

Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]

Example 2:

Input: root = [2,1,1]
Output: [[1]]

Example 3:

Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]

Constraints:

The number of the nodes in the tree will be in the range [1, 5000]
-200 <= Node.val <= 200
```

## Observations

The problem asks us to find all subtrees in a binary tree that appear more than once (i.e., are duplicates).

Two subtrees are considered duplicates if they have the same structure and node values.

We only need to return the ```root``` node of each kind of duplicate subtree, not all occurrences.

The tree can have up to ```5000``` nodes, so the solution should be efficient.

## Solution

We use a recursive Depth-First Search (```DFS```) to traverse the tree.

For each subtree, we serialize its structure and values into a string (e.g., ```"2,#,#"```for a node with value 2 and no children).

We use a hash table (```dictionary```) to count how many times each serialized subtree appears.

When a subtree's serialization appears for the second time, we add its ```root``` node to the result list.

This way, we efficiently find all duplicate subtrees by comparing their serialized forms.

## Tags

binary tree, recursion, hash table
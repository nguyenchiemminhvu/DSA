## Problem

https://leetcode.com/problems/finish-time-of-tasks-i/description/

```
You are given an integer n representing the number of tasks in a project, numbered from 0 to n - 1. These tasks are connected as a tree rooted at task 0. This is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that task ui is the parent of task vi.

You are also given an array baseTime of length n, where baseTime[i] represents the time to complete task i.

The finish time of each task is calculated as follows:

- Leaf task: The finish time is baseTime[i].
- Non-leaf task:
  - Let earliest be the minimum finish time among its children, and latest be the maximum finish time among its children.
  - Let ownDuration be (latest - earliest) + baseTime[i].
  - The finish time of task i is latest + ownDuration.

Return the finish time of the root task 0.

Constraints:

1 <= n <= 10^5
edges.length = n - 1
0 <= ui, vi <= n - 1
ui != vi
The input is generated such that edges represents a valid tree.
baseTime.length == n
1 <= baseTime[i] <= 10^5
The finish time of every task is guaranteed to be less than 2^53.
```

## Observations

The tasks form a rooted tree where we need to compute a finish time for each node bottom-up.

For a leaf node, the finish time is simply its own `baseTime`.

For an internal node, the finish time depends on the finish times of all its children:
- `earliest` = min finish time among children
- `latest` = max finish time among children
- `ownDuration` = `(latest - earliest) + baseTime[i]`
- `finishTime[i]` = `latest + ownDuration`

Note that `latest + ownDuration = latest + (latest - earliest) + baseTime[i] = 2 * latest - earliest + baseTime[i]`.

This is a standard post-order tree traversal: compute children first, then the parent.

Since `n` can be up to `10^5`, recursion depth could cause a stack overflow for a linear chain tree. An iterative post-order traversal (or explicit stack) is safer.

## Solution

**Build the tree:**
- Parse `edges` to build an adjacency list of children for each node (since `edges[i] = [parent, child]`).

**Post-order DFS:**
- Use a stack-based iterative DFS to process nodes in post-order.
- For each node, once all children are processed, compute its finish time:
  - If no children: `finishTime[node] = baseTime[node]`
  - Otherwise: `finishTime[node] = 2 * latest - earliest + baseTime[node]`

**Return** `finishTime[0]`.

**Complexity:**
- Time: O(n) — each node is visited once.
- Space: O(n) — for the children list and finish time array.

## Tags

tree, depth-first search, post-order traversal

## Problem

https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/description/

You are given the `root` of a binary tree and an integer `distance`. A pair of two different **leaf** nodes of a binary tree is said to be **good** if the length of the shortest path between them is less than or equal to `distance`.

Return the number of good leaf node pairs in the tree.

**Example 1:**
```
Input: root = [1,2,3,null,4], distance = 3
Output: 1
Explanation: The leaf nodes are 3 and 4. Shortest path = 3. This is the only good pair.
```

**Example 2:**
```
Input: root = [1,2,3,4,5,6,7], distance = 3
Output: 2
Explanation: Good pairs are [4,5] (path=2) and [6,7] (path=2).
```

**Example 3:**
```
Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
Output: 1
Explanation: The only good pair is [2,5].
```

**Constraints:**
- Number of nodes in the tree: `[1, 2^10]`
- `1 <= Node.val <= 100`
- `1 <= distance <= 10`

---

## Observations

1. **Leaf-to-leaf path through LCA.** The shortest path between any two leaf nodes must pass through their Lowest Common Ancestor (LCA). If a leaf is at depth `d1` below the LCA and another is at depth `d2`, the path length is `d1 + d2`.

2. **Post-order DFS is natural here.** To count pairs at each node acting as LCA, we need to know the distances of all reachable leaves in the left and right subtrees. A post-order DFS lets each node collect this information from its children before combining.

3. **What to return from each node.** Each `dfs(node)` call returns a list of distances from `node` to every leaf reachable in its subtree. A leaf node returns `[1]` (distance 1 from itself — the step the parent will take to reach it).

4. **Counting pairs at each internal node.** For a node with left leaf distances `left` and right leaf distances `right`, every combination `(l, r)` where `l + r <= distance` is a good pair whose LCA is this node. This avoids double-counting since left and right subtrees are disjoint.

5. **Pruning with `distance`.** When propagating distances upward, any leaf distance `d` that already equals `distance` can never form a good pair with any other leaf (since adding at least 1 more step would exceed `distance`). Filtering those out keeps the lists small. With `distance <= 10`, each list has at most 10 entries, so the pairwise check is O(distance²) per node — effectively O(1).

6. **Overall complexity.** O(N · distance²) time, O(N · distance) space for the recursion stack and distance lists.

---

## Solution

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def countPairs(self, root: Optional[TreeNode], distance: int) -> int:
        self.res = 0

        def dfs(root):
            if not root:
                return []

            # Leaf node: distance from itself to itself is 0,
            # but return [1] because the parent is 1 step away.
            if not root.left and not root.right:
                return [1]

            left = dfs(root.left)   # distances from root.left to its leaves
            right = dfs(root.right) # distances from root.right to its leaves

            # Current node is the LCA for every (l, r) cross-pair.
            # l + r = total path length between the two leaves.
            for l in left:
                for r in right:
                    if l + r <= distance:
                        self.res += 1

            # Propagate distances upward, incremented by 1 (one more edge to parent).
            # Prune any distance that already equals `distance` — it can never
            # combine with anything to stay within the limit.
            new_dist = []
            for d in left + right:
                if d + 1 <= distance:
                    new_dist.append(d + 1)

            return new_dist

        dfs(root)
        return self.res
```

### Step-by-step trace (Example 1: `[1,2,3,null,4]`, distance=3)

```
        1
       / \
      2   3
       \
        4
```

- `dfs(4)` → leaf → returns `[1]`
- `dfs(3)` → leaf → returns `[1]`
- `dfs(2)`: left=`[]`, right=`[1]`
  - No left leaves, no pairs counted.
  - Propagate: `[1+1]` = `[2]`
- `dfs(1)`: left=`[2]` (leaf 4), right=`[1]` (leaf 3)
  - Check pair: `2 + 1 = 3 <= 3` → `res = 1`
  - Propagate: `[3, 2]` but `3+1=4 > 3` and `2+1=3 <= 3` → `[3]` (not used further)
- Return `self.res = 1` ✓

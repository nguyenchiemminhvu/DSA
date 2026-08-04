## Problem

https://leetcode.com/problems/make-costs-of-paths-equal-in-a-binary-tree/description/

You are given a **perfect binary tree** with `n` nodes numbered `1` to `n`. The root is node `1`, and each node `i` has:
- Left child: `2 * i`
- Right child: `2 * i + 1`

Each node has a cost given by a 0-indexed array `cost` where `cost[i]` is the cost of node `i + 1`.

You may increment the cost of any node by 1 any number of times. Return the **minimum number of increments** needed so that the total cost of every root-to-leaf path is equal.

**Examples:**

```
Input: n = 7, cost = [1,5,2,2,3,3,1]
Output: 6
Explanation: Increment node 4 once, node 3 three times, node 7 twice.
All root-to-leaf paths then sum to 9. Total increments = 6.

Input: n = 3, cost = [5,3,3]
Output: 0
Explanation: Both paths already sum to 8.
```

**Constraints:**
- `3 <= n <= 10^5`
- `n + 1` is a power of 2 (guarantees a perfect binary tree)
- `1 <= cost[i] <= 10^4`

---

## Observations

1. **Perfect binary tree structure:** All leaves are at the same depth, and every internal node has exactly two children. This means every root-to-leaf path has the same number of nodes — a key property that makes the problem tractable.

2. **Only increments are allowed:** We cannot decrease any cost. So to equalize two sibling subtrees, we must bring the *cheaper* one up to match the *more expensive* one. This greedy insight is fundamental.

3. **Bottom-up equalization:** Consider any two sibling leaf nodes. Their parent's contribution is shared by both paths, so we only need to equalize costs at the sibling level. The number of increments needed is `abs(left_subtree_sum - right_subtree_sum)`. We then "merge" the two siblings into a single representative value equal to `max(left, right)` and propagate upward.

4. **Greedy is optimal:** At each internal node, we are forced to raise the smaller child's path sum to match the larger one. Raising the larger would only increase the total increments unnecessarily. So always matching to the max is the minimum cost strategy.

5. **The root's cost doesn't matter for equalization:** By the time we reach the root, both subtrees have already been made equal internally, and the root's cost is added to every path uniformly — it does not create any imbalance.

---

## Solution Explanation

The solution uses a **post-order DFS** (process children before parent).

```python
class Solution:
    def minIncrements(self, n: int, cost: List[int]) -> int:
        res = 0
        def dfs(root):
            nonlocal res
            if root > n:
                return 0
            
            left = dfs(root * 2)
            right = dfs(root * 2 + 1)
            diff = abs(right - left)
            res += diff
            return cost[root - 1] + max(left, right)

        dfs(1)
        return res
```

**Step-by-step walkthrough:**

- `dfs(root)` returns the **maximum path sum** from `root` down to any leaf in its subtree (after all equalizations within that subtree have been applied).

- **Base case:** If `root > n`, we are beyond a leaf node (null child), return `0`.

- **Recursive case:**
  1. Recursively get `left` and `right` — the already-equalized max path sums of the left and right subtrees.
  2. Compute `diff = abs(right - left)`. This is how many increments are needed at this level to make both children's path sums equal.
  3. Accumulate `diff` into the global result `res`.
  4. Return `cost[root - 1] + max(left, right)` — the current node's cost plus the larger of the two (now equalized) subtree sums. The larger is returned because the smaller side was just raised to match it, so both sides are now equal to `max(left, right)`.

**Example trace for `n = 7, cost = [1,5,2,2,3,3,1]`:**

```
Tree layout:
         1 (cost=1)
        / \
      2(5)  3(2)
      / \   / \
    4(2)5(3)6(3)7(1)
```

- `dfs(4)` → no children → returns `cost[3] = 2`
- `dfs(5)` → no children → returns `cost[4] = 3`
- `dfs(2)`: left=2, right=3, diff=1, res=1 → returns `5 + max(2,3) = 8`
- `dfs(6)` → returns `cost[5] = 3`
- `dfs(7)` → returns `cost[6] = 1`
- `dfs(3)`: left=3, right=1, diff=2, res=1+2=3 → returns `2 + max(3,1) = 5`
- `dfs(1)`: left=8, right=5, diff=3, res=3+3=6 → returns `1 + max(8,5) = 9`

**Answer: 6** ✓

**Complexity:**
- **Time:** O(n) — each node is visited exactly once.
- **Space:** O(log n) — recursion depth equals the height of the perfect binary tree.

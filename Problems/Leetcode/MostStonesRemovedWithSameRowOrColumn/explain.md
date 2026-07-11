## Problem

https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/

On a 2D plane, `n` stones are placed at integer coordinate points. A stone can be removed if it shares **the same row or the same column** as another stone that has not yet been removed. Return the **largest possible number of stones** that can be removed.

---

## Observations

1. **Shared row/column creates a connection.** If stone A and stone B share a row or column, removing one does not prevent the other from being removed later (as long as a third connected stone exists). This means the order of removal matters less than the *structure* of connections.

2. **Connected components are the key.** Define two stones as connected if they share a row or column — directly or transitively (A-B via row, B-C via column ⟹ A, B, C are one component). Within any connected component of size $k$, we can always remove exactly $k - 1$ stones, leaving exactly one behind.

   - **Why always $k-1$?** By induction: in any component with $\geq 2$ stones, there must exist at least one stone that shares a row/column with another (otherwise the component would be disconnected). Remove that stone. The remaining $k-1$ stones still form a connected component. Repeat until 1 stone is left.

3. **Answer formula:**
$$\text{answer} = n - \text{(number of connected components)}$$

---

## Solution Explanation

The solution uses **Union-Find (DSU)** to identify connected components among the stones.

**Step 1 — Build the DSU:**  
Each stone gets an index `0` to `n-1`. For every pair of stones `(i, j)`, if they share the same row (`xi == xj`) or the same column (`yi == yj`), call `dsu.union(i, j)` to merge them into one component.

**Step 2 — Count components:**  
After all unions, iterate over all stone indices and collect their root representatives via `dsu.find(i)`. The number of distinct roots equals the number of connected components.

**Step 3 — Return `n - components`:**  
Each component contributes exactly 1 stone that cannot be removed, so the maximum removable count is `n - len(components)`.

**Example walkthrough (Example 1):**
```
stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
```
- `[0,0]` and `[0,1]` share row 0 → union(0,1)
- `[0,0]` and `[1,0]` share col 0 → union(0,2)
- `[0,1]` and `[2,1]` share col 1 → union(1,4)
- `[1,2]` and `[2,2]` share col 2 → union(3,5)
- `[2,1]` and `[2,2]` share row 2 → union(4,5)

All 6 stones end up in **1 component** → answer = 6 - 1 = **5** ✓

**Complexity:**
- Time: $O(n^2 \cdot \alpha(n))$ — all pairs checked, each union/find is near $O(1)$
- Space: $O(n)$

> **Note:** The `pos_to_id` dictionary built in the solution is unused — the indices `0..n-1` serve directly as DSU node IDs.

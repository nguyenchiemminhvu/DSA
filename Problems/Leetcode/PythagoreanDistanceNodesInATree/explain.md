## Problem

https://leetcode.com/problems/pythagorean-distance-nodes-in-a-tree/description/

Given an integer `n` and an undirected tree with `n` nodes (0 to n-1), represented by `edges`, and three distinct target nodes `x`, `y`, `z`:

For every node `u`, compute:
- `dx` = distance from `u` to `x`
- `dy` = distance from `u` to `y`
- `dz` = distance from `u` to `z`

Node `u` is **special** if `(dx, dy, dz)` forms a **Pythagorean triplet** — i.e., when sorted as `a ≤ b ≤ c`, they satisfy `a² + b² = c²`.

Return the count of special nodes.

---

## Examples

**Example 1:** `n=4, edges=[[0,1],[0,2],[0,3]], x=1, y=2, z=3` → Output: `3`

- Node 1: distances (0, 2, 2) → 0² + 2² = 2² ✓
- Node 2: distances (2, 0, 2) → 0² + 2² = 2² ✓
- Node 3: distances (2, 2, 0) → 0² + 2² = 2² ✓

**Example 2:** `n=4, edges=[[0,1],[1,2],[2,3]], x=0, y=3, z=2` → Output: `0`

**Example 3:** `n=4, edges=[[0,1],[1,2],[1,3]], x=1, y=3, z=0` → Output: `1`

---

## Constraints

- `4 <= n <= 10^5`
- `edges.length == n - 1`
- `x`, `y`, `z` are pairwise distinct

---

## Ideas

### Core Observations

1. **Distance in a tree** between two nodes is unique (there is only one path). We can compute distances from any source node using BFS in O(n).

2. We need distances from **3 sources** (`x`, `y`, `z`) to **all nodes**. Run BFS three times → O(3n) = O(n).

3. For each node `u`, collect `[dx, dy, dz]`, sort them, and check if `a² + b² = c²`.

---

### Algorithm

```
1. Build adjacency list from edges.
2. BFS from x → dist_x[0..n-1]
3. BFS from y → dist_y[0..n-1]
4. BFS from z → dist_z[0..n-1]
5. For each node u in [0, n-1]:
     a = [dist_x[u], dist_y[u], dist_z[u]]
     sort(a)
     if a[0]*a[0] + a[1]*a[1] == a[2]*a[2]:
         count++
6. Return count
```

---

### Pythagorean Check

Sort the three distances: `a ≤ b ≤ c`.  
Check: `a*a + b*b == c*c`.

Note: `a = 0` is valid — it gives `b² = c²`, i.e., `b == c`, which is a degenerate triplet (still satisfies the formula).

---

### Complexity

| Step | Time | Space |
|------|------|-------|
| Build graph | O(n) | O(n) |
| 3× BFS | O(n) | O(n) |
| Check all nodes | O(n) | O(1) |
| **Total** | **O(n)** | **O(n)** |


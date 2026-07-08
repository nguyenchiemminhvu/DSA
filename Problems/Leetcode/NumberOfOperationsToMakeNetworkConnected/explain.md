## Problem

https://leetcode.com/problems/number-of-operations-to-make-network-connected/

Given `n` computers numbered `0` to `n-1` connected by ethernet cables. You can **extract** a cable between two directly connected computers and **place** it between any two disconnected computers.

Return the **minimum number of cable moves** needed to make all computers connected. Return `-1` if it is not possible.

---

## Observations

1. **Minimum cables needed**: To connect `n` computers into a single network, you need at least `n - 1` cables (a spanning tree). If `connections.length < n - 1`, there are simply not enough cables — return `-1` immediately.

2. **Redundant cables (cycles)**: When a cable connects two computers that are already in the same connected component, it creates a cycle. That cable is **redundant** — it can be safely removed and reused elsewhere without disconnecting anything.

3. **Connected components**: After processing all connections, the network may consist of multiple isolated groups (components). Each group is internally connected but cannot reach the others.

4. **Key insight**: To merge `C` connected components into a single network, you need exactly `C - 1` cable moves — just like connecting `C` islands with bridges. Each move takes one redundant cable and links two previously isolated components.

5. **Guarantee of enough redundant cables**: If the total number of cables is `≥ n - 1`, we are always guaranteed to have enough redundant cables to perform the required `C - 1` moves. This is because:
   - A spanning tree of `n` nodes uses exactly `n - 1` edges.
   - Any extra edge beyond `n - 1` is a redundant (cycle-forming) cable.
   - With `C` components, the union of their spanning trees uses at most `n - C` edges, leaving at least `connections.length - (n - C)` redundant cables. Since `connections.length ≥ n - 1`, redundant cables `≥ n - 1 - (n - C) = C - 1` ✓

---

## Approach — Union-Find (Disjoint Set Union)

**Why Union-Find?**
This problem is fundamentally about grouping nodes into connected components and counting how many disconnected groups exist. DSU does exactly this in near-linear time.

**Steps:**

1. **Early exit**: If `len(connections) < n - 1`, return `-1`.

2. **Initialize DSU** with `n` nodes, each in its own component.

3. **Process each connection `[u, v]`**:
   - Call `union(u, v)`.
   - If `u` and `v` are already in the same component → this cable is **redundant** (no action needed beyond recognizing it).
   - Otherwise → merge the two components.

4. **Count components**: After all unions, count the number of distinct roots. Each unique root represents one connected component.

5. **Answer**: `number_of_components - 1`
   - We need exactly this many cable moves to bridge all components together.

**DSU Optimizations used:**
- **Path compression** in `find`: flattens the tree so future lookups are faster.
- **Union by rank**: always attaches the shorter tree under the taller one, keeping trees balanced.

Together these give an amortized time per operation of $O(\alpha(n))$, where $\alpha$ is the inverse Ackermann function — effectively constant for all practical inputs.

**Complexity:**
- **Time**: $O(n + E \cdot \alpha(n))$, where $E$ = number of connections
- **Space**: $O(n)$ for the DSU arrays

---

## Walkthrough — Example 1

```
n = 4, connections = [[0,1],[0,2],[1,2]]
```

- `len(connections) = 3 ≥ n - 1 = 3` → proceed.
- Process `[0,1]`: union 0 and 1 → components: `{0,1}, {2}, {3}`
- Process `[0,2]`: union 0 and 2 → components: `{0,1,2}, {3}`
- Process `[1,2]`: 1 and 2 are already connected → **redundant cable**
- Components = 2 → answer = `2 - 1 = 1` ✓

## Walkthrough — Example 2

```
n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
```

- `len(connections) = 5 ≥ n - 1 = 5` → proceed.
- After processing: components = `{0,1,2,3}, {4}, {5}`
- Redundant cables: `[1,2]` and `[1,3]` (both form cycles in component 0)
- Components = 3 → answer = `3 - 1 = 2` ✓

## Walkthrough — Example 3

```
n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
```

- `len(connections) = 4 < n - 1 = 5` → return `-1` ✓

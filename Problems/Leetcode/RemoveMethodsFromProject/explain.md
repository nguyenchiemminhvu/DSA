## Problem

https://leetcode.com/problems/remove-methods-from-project/description/

Given `n` methods (numbered `0` to `n-1`) in a project and a known bug in method `k`, find and remove all **suspicious** methods — method `k` and any method it invokes directly or indirectly. However, the suspicious group can only be removed if **no method outside the group invokes any method inside it**. Return the remaining methods after removal, or all methods if removal is not possible.

---

## Observations

1. **Graph structure**: The `invocations` array defines a **directed graph** where an edge `[a, b]` means method `a` calls method `b`.

2. **Suspicious set**: Starting from method `k`, all methods reachable via directed edges (directly or indirectly) form the suspicious set. This is a standard **graph reachability** problem solvable with BFS or DFS.

3. **Removal condition**: The suspicious group can only be removed if no method *outside* the group has an edge pointing *into* the group. Formally, for every edge `[a, b]`: if `a` is **not** suspicious and `b` **is** suspicious, removal is blocked.

4. **All-or-nothing**: Either we remove every method in the suspicious set, or we remove none. There is no partial removal.

5. **Edge cases**:
   - If `k` is part of a cycle, all methods in that cycle become suspicious.
   - If every method is suspicious, the result is an empty array `[]`.

---

## Approach

**Step 1 — Build the directed graph**  
Convert `invocations` into an adjacency list for efficient traversal.

**Step 2 — Find all suspicious methods (DFS/BFS from `k`)**  
Perform a DFS or BFS starting at node `k`. Every visited node is added to the `suspicious` set.

**Step 3 — Check if removal is safe**  
Iterate over every edge `[a, b]`:
- If `a` is **not** in `suspicious` and `b` **is** in `suspicious` → a non-suspicious method depends on a suspicious one → **cannot remove**.

**Step 4 — Return the result**
- If removal is safe → return all methods **not** in `suspicious`.
- Otherwise → return all methods `[0, 1, ..., n-1]`.

**Complexity**:
- Time: $O(n + E)$ where $E$ = number of invocations (graph build + DFS + edge scan).
- Space: $O(n + E)$ for the adjacency list and visited set.

## Problem

https://leetcode.com/problems/satisfiability-of-equality-equations/description/

Given an array of strings `equations` representing relationships between single-letter variables, where each string is either `"xi==yi"` (equality) or `"xi!=yi"` (inequality), return `true` if it is possible to assign integers to variable names so as to satisfy **all** given equations simultaneously, or `false` otherwise.

---

## Observations

1. **Variables are bounded**: All variables are lowercase letters `a`–`z`, so there are at most 26 distinct variables. This means the problem space is very small.

2. **Equality is an equivalence relation**: If `a==b` and `b==c`, then `a==c` must also hold. Equality groups variables into **connected components** — all variables in the same component must share the same integer value.

3. **Inequality constrains components, not values directly**: A constraint `a!=b` is only violated when `a` and `b` belong to the **same equivalence component** (i.e., they are forced to be equal by the `==` equations).

4. **Two-phase processing is key**: Processing `==` and `!=` equations together in one pass is error-prone. However, if we first establish all equality groups and then validate inequalities, the logic becomes clean and correct. Order matters: a `!=` constraint seen before a `==` constraint might look valid but become violated later.

5. **Self-inequality `a!=a` is always false**: If any equation states a variable is not equal to itself, the answer is immediately `false`, and this is naturally caught by the algorithm.

---

## Approach — Union-Find (Disjoint Set Union)

The equality relation partitions variables into groups. This is exactly the **Union-Find** (DSU) data structure's purpose: efficiently grouping elements and querying whether two elements are in the same group.

### Algorithm

**Phase 1 — Union all equalities**

Iterate through all equations. For each `"xi==yi"`, union `xi` and `yi` into the same component.

**Phase 2 — Validate all inequalities**

Iterate through all equations again. For each `"xi!=yi"`, check if `find(xi) == find(yi)`. If they share the same root, the inequality is violated → return `false`.

If no violation is found, return `true`.

### Why two passes?

Consider `["a!=b", "a==b"]`. On the first pass we see `a!=b`, which looks fine since they aren't unioned yet. But after processing `a==b`, they become the same component. Processing inequalities only **after** all equalities are unioned guarantees correctness.

### Complexity

| | Value |
|---|---|
| Time | $O(N \cdot \alpha(26))$ ≈ $O(N)$ — nearly linear; $\alpha$ is the inverse Ackermann function |
| Space | $O(26)$ = $O(1)$ — fixed-size DSU for 26 letters |

### Pseudocode

```
initialize parent[26] = {0, 1, 2, ..., 25}   // each letter is its own root

function find(x):
    if parent[x] != x:
        parent[x] = find(parent[x])           // path compression
    return parent[x]

function union(x, y):
    parent[find(x)] = find(y)

// Phase 1: union all "==" pairs
for each equation in equations:
    if equation[1] == '=':
        union(equation[0] - 'a', equation[3] - 'a')

// Phase 2: check all "!=" pairs
for each equation in equations:
    if equation[1] == '!':
        if find(equation[0] - 'a') == find(equation[3] - 'a'):
            return false

return true
```

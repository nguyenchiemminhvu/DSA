## Problem

https://leetcode.com/problems/queries-on-a-permutation-with-key/description/

You are given a permutation `P = [1, 2, 3, ..., m]` and an array `queries`. For each `queries[i]`, find the **0-based index** of `queries[i]` in `P`, record it as the result, then **move** `queries[i]` to the **front** of `P`. Return all recorded results.

---

## Observations

1. **Dynamic reordering**: The permutation changes after every query, so the position of a value shifts constantly. We cannot precompute positions statically.

2. **Move-to-front pattern**: This is the classic *Move-To-Front (MTF)* heuristic — recently accessed elements cluster near the front, making future accesses to the same element cheap.

3. **Bottleneck of the naive approach**: Each query does two expensive operations on a Python list:
   - `p.index(query)` — O(m) linear scan to find the position.
   - List reconstruction `[query] + p[:idx] + p[idx+1:]` — O(m) copy.
   - Total: **O(m × q)** where `q = len(queries)`. With `m, q ≤ 10³` this is ~10⁶ ops, which is acceptable for the given constraints but does not scale.

4. **Key insight for optimization**: We need a data structure that supports:
   - **Find by value** in O(log m)
   - **Delete from arbitrary position** in O(log m)
   - **Insert at front** in O(log m)
   
   A **Binary Indexed Tree (Fenwick Tree)** over a virtual array of size `2m` achieves exactly this.

---

## Naive Solution — O(m × q)

```python
class Solution:
    def processQueries(self, queries: List[int], m: int) -> List[int]:
        p = [i for i in range(1, m + 1)]
        res = []
        for query in queries:
            idx = p.index(query)           # O(m) scan
            p = [query] + p[:idx] + p[idx + 1:]  # O(m) reconstruction
            res.append(idx)
        return res
```

Simple and correct, but rebuilds the entire list on every query.

---

## Optimized Solution — Binary Indexed Tree (Fenwick Tree) — O(q log m)

### Core Idea

Instead of maintaining the actual list, we use a **Fenwick Tree** (BIT) over a virtual index space of size `2m`:

- Slots `[m+1 .. 2m]` are pre-filled with the initial permutation `[1..m]`: value `v` starts at virtual slot `m + v`.
- Slots `[1 .. m]` are reserved as a "prepend zone". Each time we move a value to the front, we place it in the next available slot counting *down* from `m` (i.e., slot `m`, `m-1`, ...).
- The BIT stores **1** at each occupied slot and **0** elsewhere.
- The **rank** (0-based position) of a value at virtual slot `s` = prefix sum `BIT.query(s - 1)` = number of occupied slots before `s`.

### Operations

| Operation | How | Cost |
|---|---|---|
| Find position of value `v` | Look up its current virtual slot `pos[v]`, then compute prefix sum up to `pos[v] - 1` | O(log m) |
| Remove from current slot | Set BIT at `pos[v]` to 0 | O(log m) |
| Insert at front | Decrement a free-slot pointer `cur`, set BIT at `cur` to 1, update `pos[v] = cur` | O(log m) |

### Implementation

```python
from typing import List

class BIT:
    def __init__(self, n: int):
        self.n = n
        self.tree = [0] * (n + 1)

    def update(self, i: int, delta: int):
        """Add delta at position i (1-indexed)."""
        while i <= self.n:
            self.tree[i] += delta
            i += i & (-i)

    def query(self, i: int) -> int:
        """Prefix sum [1..i]."""
        s = 0
        while i > 0:
            s += self.tree[i]
            i -= i & (-i)
        return s


class Solution:
    def processQueries(self, queries: List[int], m: int) -> List[int]:
        size = 2 * m
        bit = BIT(size)
        pos = {}  # pos[v] = current virtual slot of value v

        # Initialize: value v sits at virtual slot m + v
        for v in range(1, m + 1):
            slot = m + v
            pos[v] = slot
            bit.update(slot, 1)

        cur = m          # next free prepend slot (counts down: m, m-1, ...)
        res = []

        for query in queries:
            s = pos[query]
            # 0-based rank = number of filled slots strictly before s
            rank = bit.query(s - 1)
            res.append(rank)

            # Remove from current slot
            bit.update(s, -1)

            # Move to front: use next free prepend slot
            bit.update(cur, 1)
            pos[query] = cur
            cur -= 1

        return res
```

### Walkthrough — Example 1: queries = [3,1,2,1], m = 5

Virtual slots after init (m=5, so slots 6..10 hold values 1..5):

```
slot:  6  7  8  9  10
val:   1  2  3  4   5
BIT:   1  1  1  1   1
cur = 5  (next free prepend slot)
```

- **query=3**, slot=8, rank=query(7)=2 → result=**2**. Remove slot 8, prepend at slot 5. `cur=4`.
- **query=1**, slot=6, rank=query(5)=1 → result=**1**. Remove slot 6, prepend at slot 4. `cur=3`.
- **query=2**, slot=7, rank=query(6)=2 → result=**2**. Remove slot 7, prepend at slot 3. `cur=2`.
- **query=1**, slot=4, rank=query(3)=1 → result=**1**. Remove slot 4, prepend at slot 2. `cur=1`.

Output: `[2, 1, 2, 1]` ✓

### Complexity

| | Time | Space |
|---|---|---|
| Naive | O(m × q) | O(m) |
| BIT-optimized | **O(q log m)** | O(m) |

With `m = q = 10³`, naive does ~10⁶ ops vs BIT's ~10⁴. The BIT approach scales to `m = 10⁵` without issue.

---

## Alternative Optimization — Order-Statistic Tree

A **balanced BST with order statistics** (e.g., an augmented Red-Black Tree or a Treap) stores `(slot, value)` pairs and supports:
- `find_by_order(k)` — find the k-th element in O(log m)
- `order_of_key(x)` — find the rank of element x in O(log m)

In Python this can be approximated with `from sortedcontainers import SortedList`, giving the same O(log m) per query with slightly simpler code, though the BIT approach above is more cache-friendly and faster in practice.


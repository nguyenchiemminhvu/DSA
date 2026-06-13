## Problem

https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/description/

Given a 0-indexed array `heights` of positive integers and an array `queries` where each `queries[i] = [a, b]`, a person at building `i` can move to building `j` only if `i < j` and `heights[i] < heights[j]`.

For each query, Alice is at building `a` and Bob is at building `b`. Find the **index of the leftmost building** where both can meet. Return `-1` if impossible.

---

## Observations

**Observation 1 — Trivial case (same building):**  
If `a == b`, Alice and Bob are already at the same building. Answer is `a`.

**Observation 2 — Direct meeting (one can walk to the other):**  
WLOG assume `a < b` (swap if needed). If `heights[b] > heights[a]`, Alice can move directly from `a` to `b`. Answer is `b`.

**Observation 3 — Need a third building:**  
When `heights[b] <= heights[a]` (with `a < b`), neither can walk into the other's position, so they must both walk to some building `k > b` where:
- `heights[k] > heights[a]` (Alice can jump from `a`)
- `heights[k] > heights[b]` (Bob can jump from `b`)

Since `heights[b] <= heights[a]`, the combined requirement simplifies to `heights[k] > max(heights[a], heights[b]) = heights[a]`.

We want the **leftmost** such `k`.

**Observation 4 — Monotonic stack structure:**  
Among all indices to the right of `b`, many are irrelevant: if index `j > k` has `heights[j] >= heights[k]`, then `k` can never be the answer when `j` exists (since `k` is dominated). The candidates form a **strictly increasing height sequence** from left to right — a classic monotonic stack.

---

## Solution

The algorithm uses **offline processing** (sort queries) + **monotonic stack** + **binary search**.

### Step 1 — Handle easy cases inline

For each query `[a, b]` (with `a <= b` after potential swap):
- If `a == b` → answer is `a`
- If `heights[b] > heights[a]` → answer is `b`

### Step 2 — Sort queries by `max(a, b)` descending

Hard queries need to search among buildings to the right of `max(a, b)`. By sorting queries in **descending order of the right endpoint** `y = max(a, b)`, we can build the monotonic stack **incrementally** from right to left and reuse it across queries.

### Step 3 — Build a monotonic stack (decreasing heights, left to right)

A `deque` maintains a window of candidate indices to the right of the current query's `y`. The stack is maintained as **strictly increasing heights from front to back** (smallest height at front = leftmost index, largest height at back = rightmost index):

```
while idx > y:
    while st and arr[st[0]] <= arr[idx]:
        st.popleft()          # remove dominated elements from front
    st.appendleft(idx)        # prepend current index
    idx -= 1
```

After this loop, the deque contains exactly the indices `> y` that are *not dominated* by any earlier (leftward) index — i.e., they form a strictly increasing height sequence left to right.

**Invariant:** `st[0]` is the leftmost candidate (smallest index, smallest height among candidates), `st[-1]` is the rightmost (largest index, largest height).

### Step 4 — Binary search for the answer

We need the **leftmost** index in the stack where `heights[k] > max_h`. Since heights in the deque increase from front to back, the valid indices form a **suffix**. Binary search finds the boundary:

```
pick_idx = binary_search_leftmost(st, condition: arr[st[m]] > max_h)
```

The answer is `st[pick_idx]`.

### Why this is correct

- The monotonic stack discards indices that can never be the *leftmost* answer: if `heights[j] >= heights[k]` with `j < k`, then whenever `k` satisfies `heights[k] > max_h`, so does `j`, and `j` is a better (leftmost) answer. So `k` is never needed.
- Binary search is valid because the remaining stack has strictly increasing heights → the first element exceeding `max_h` is the leftmost valid candidate.

### Complexity

| | |
|---|---|
| **Time** | $O((n + q) \log n)$ — stack build $O(n)$, binary search per query $O(\log n)$, sort $O(q \log q)$ |
| **Space** | $O(n + q)$ |

---

## Annotated Code

```python
class Solution:
    def leftmostBuildingQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        n = len(arr)
        nq = len(queries)
        res = [-1] * nq

        # Attach original index so we can write results in order
        queries = [(i, query) for i, query in enumerate(queries)]
        # Sort by right endpoint descending so we build the stack incrementally
        queries.sort(key=lambda x: (-max(x[1]), -min(x[1])))

        st = deque()   # monotonic stack: increasing heights, left-to-right order
        idx = n - 1    # pointer into arr, moves right → left

        for i, (orig_i, (x, y)) in enumerate(queries):
            # Case 1: same building
            if x == y:
                res[orig_i] = x
                continue

            # Ensure x < y (x is left, y is right)
            if x > y:
                x, y = y, x

            # Case 2: right building is taller → meet there directly
            if arr[y] > arr[x]:
                res[orig_i] = y
                continue

            # Case 3: extend stack to cover all indices > y
            while idx > y:
                # Remove front elements dominated by arr[idx]
                while st and arr[st[0]] <= arr[idx]:
                    st.popleft()
                st.appendleft(idx)   # prepend: front = leftmost index
                idx -= 1

            # Binary search: find leftmost stack position with height > max_h
            max_h = max(arr[x], arr[y])
            pick_idx = len(st)       # default: not found
            l, r = 0, len(st) - 1
            while l <= r:
                m = l + (r - l) // 2
                if arr[st[m]] > max_h:
                    pick_idx = m
                    r = m - 1        # look for an even earlier (leftward) candidate
                else:
                    l = m + 1

            if pick_idx < len(st):
                res[orig_i] = st[pick_idx]

        return res
```

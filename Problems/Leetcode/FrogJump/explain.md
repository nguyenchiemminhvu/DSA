## Problem

https://leetcode.com/problems/frog-jump/description

A frog is crossing a river divided into units. Stones exist at certain positions (given as a sorted list). The frog starts at position `0` (first stone) and must reach the last stone. The first jump is always `1` unit. If the last jump was `k` units, the next jump must be `k-1`, `k`, or `k+1` units. The frog can only jump forward and must always land on a stone.

**Example 1:**
- Input: `stones = [0,1,3,5,6,8,12,17]`
- Output: `true`
- The frog jumps with lengths 1, 2, 2, 3, 4, 5 to reach the last stone.

**Example 2:**
- Input: `stones = [0,1,2,3,4,8,9,11]`
- Output: `false`
- The frog can reach position `4` but the next stone is at `8` (gap = 4). No stone exists in between, so crossing is impossible.

**Constraints:**
- `2 <= stones.length <= 2000`
- `0 <= stones[i] <= 2^31 - 1`
- `stones[0] == 0`
- Stones are strictly increasing.

---

## Observations

1. **State is (stone index, last jump length):** The frog's future options depend only on *where it is* and *how large its last jump was*. These two values fully define the subproblem.

2. **At most 3 choices per step:** From state `(i, k)`, the frog can jump `k-1`, `k`, or `k+1` units forward. Sizes `<= 0` are invalid and must be skipped.

3. **Overlapping subproblems:** Many different paths can converge on the same stone with the same last-jump length. Recomputing these without caching would be exponential. Memoization collapses the search into a DAG of at most O(n^2) unique states.

4. **Early exit:** The very first jump is forced to be `1`. If `stones[1] != stones[0] + 1` (second stone is not at position `1`), it is immediately impossible.

5. **Position to index map:** We need O(1) checks for whether a target position contains a stone. A hash map `{position -> index}` handles this efficiently.

6. **Jump size is bounded by O(n):** The jump length can grow by at most `1` per step. Starting from `1` over at most `n` steps, the maximum jump is O(n). Total unique states <= O(n^2).

7. **Forward-only movement prevents infinite loops:** Since the frog only jumps forward with positive jump sizes, the recursion always makes progress and naturally terminates.

---

## Solution

### Approach: Top-Down Dynamic Programming (Memoization)

**Key insight:** Define `F(i, k)` = `True` if the frog can reach the last stone, given it is currently on stone index `i` and arrived there with a jump of length `k`.

**Steps:**

1. Build `mp: {position -> index}` for O(1) stone lookups.
2. Guard: if `stones[1] != stones[0] + 1`, return `False` immediately.
3. Define `F(i, last_jump_len)` with `lru_cache`:
   - If `i == n - 1` → return `True` (frog is at the last stone).
   - If `i < 0` or `i >= n` → return `False`.
   - For each `j` in `{last_jump_len - 1, last_jump_len, last_jump_len + 1}`:
     - Skip if `j <= 0`.
     - Compute `next_pos = stones[i] + j`.
     - If `next_pos` is in `mp`, recurse with `F(mp[next_pos], j)`.
     - If any branch returns `True`, return `True`.
   - Otherwise return `False`.
4. Call `F(1, 1)`.

```python
from functools import lru_cache
from typing import List

class Solution:
    def canCross(self, stones: List[int]) -> bool:
        n = len(stones)

        # Map each stone position to its index for O(1) lookup
        mp = {}
        for i, pos in enumerate(stones):
            mp[pos] = i

        visited_state = set()

        @lru_cache(None)
        def F(i: int, last_jump_len: int) -> bool:
            if i < 0 or i >= n:
                return False
            if i == n - 1:
                return True

            # Already explored this state and it led nowhere
            if (i, last_jump_len) in visited_state:
                return False
            visited_state.add((i, last_jump_len))

            for j in range(last_jump_len - 1, last_jump_len + 2):
                if j <= 0:
                    continue
                next_pos = stones[i] + j
                if next_pos not in mp:
                    continue
                next_idx = mp[next_pos]
                if F(next_idx, j):
                    return True
            return False

        # The first jump must be exactly 1 unit
        if stones[1] != stones[0] + 1:
            return False
        return F(1, 1)
```

**Trace on Example 1** (`[0, 1, 3, 5, 6, 8, 12, 17]`):

| Call | Stone pos | Last jump | Next candidates | Result |
|------|-----------|-----------|-----------------|--------|
| F(1, 1) | 1 | 1 | pos 2(no stone), 3 ✓ | F(2, 2) |
| F(2, 2) | 3 | 2 | pos 4(no), 5 ✓, 6 ✓ | F(3, 2) |
| F(3, 2) | 5 | 2 | pos 4(no), 6 ✓, 7(no) | F(4, 1) ... |
| F(4, 1) | 6 | 1 | pos 6(skip<=0), 7(no), 8 ✓ | F(5, 2) |
| F(5, 2) | 8 | 2 | pos 9(no), 10(no), 11(no) | tries deeper... |
| ... | ... | ... | ... | eventually reaches index 7 (pos 17) ✓ |

**Complexity:**
- **Time:** O(n²) — at most `n` stone indices × O(n) possible jump lengths = O(n²) unique states, each doing O(1) work.
- **Space:** O(n²) for the memoization cache, O(n) for the recursion stack.

---

# Tags

`Dynamic Programming` `Memoization` `Hash Map` `DFS`

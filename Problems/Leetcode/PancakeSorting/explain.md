```markdown
## Problem

https://leetcode.com/problems/pancake-sorting/description/

Given an array of integers `arr`, sort the array by performing a series of **pancake flips**.

In one pancake flip:
- Choose an integer `k` where `1 <= k <= arr.length`.
- Reverse the sub-array `arr[0..k-1]` (0-indexed).

Return an array of the `k`-values corresponding to a sequence of pancake flips that sort `arr`. Any valid answer that sorts the array within `10 * arr.length` flips is accepted.

**Example 1:**
```
Input:  arr = [3, 2, 4, 1]
Output: [4, 2, 4, 3]

Starting state: [3, 2, 4, 1]
After flip k=4: [1, 4, 2, 3]   ← reverse entire array
After flip k=2: [4, 1, 2, 3]   ← reverse first 2 elements
After flip k=4: [3, 2, 1, 4]   ← reverse first 4 elements
After flip k=3: [1, 2, 3, 4]   ← reverse first 3 elements ✓
```

**Example 2:**
```
Input:  arr = [1, 2, 3]
Output: []   ← already sorted
```

**Constraints:**
- `1 <= arr.length <= 100`
- `1 <= arr[i] <= arr.length`
- All integers in `arr` are unique (a permutation of `1..n`).

---

## Observations

1. **A single flip `k` only moves elements within `arr[0..k-1]`** — it cannot touch anything at index `k` or beyond. This means once an element is correctly placed at the end of the unsorted region, we never need to touch it again.

2. **Placing the largest element first is the key insight.** If we can put the current maximum into its correct final position in each round, we reduce the problem size by 1 each iteration — similar to Selection Sort, but using only prefix reversals.

3. **At most 2 flips are needed to place one element:**
   - **Flip 1 (`k = max_idx + 1`):** Bring the maximum to the front (`arr[0]`) by reversing the prefix up to and including it.
   - **Flip 2 (`k = i + 1`):** Bring the maximum from the front to its correct final position `i` by reversing the whole unsorted prefix.
   - Special case: if the maximum is already at the front (`max_idx == 0`), skip Flip 1.
   - Special case: if the maximum is already at position `i`, skip both flips entirely.

4. **Total flips ≤ 2 * (n - 1)**, which is well within the `10 * n` limit.

5. **The array shrinks from the right.** After each round, the rightmost unsorted position `i` is correctly filled, so we decrement `i` and repeat on `arr[0..i-1]`.

---

## Solution Explanation

```python
class Solution:
    def pancakeSort(self, arr: List[int]) -> List[int]:
        n = len(arr)

        res = []
        for i in range(n - 1, 0, -1):                        # (1)
            max_idx = arr.index(max(arr[0:i + 1]))            # (2)
            if max_idx < i:                                   # (3)
                if max_idx != 0:                              # (4)
                    res.append(max_idx + 1)
                    arr[0:max_idx + 1] = arr[0:max_idx + 1][::-1]
                res.append(i + 1)                             # (5)
                arr[0:i + 1] = arr[0:i + 1][::-1]
        return res
```

**Step-by-step walkthrough:**

| Line | What it does |
|------|-------------|
| **(1)** `for i in range(n-1, 0, -1)` | Iterate from the last unsorted index down to `1`. Each round places the correct element at position `i`. |
| **(2)** `max_idx = arr.index(max(...))` | Find the index of the maximum element in the still-unsorted prefix `arr[0..i]`. |
| **(3)** `if max_idx < i` | If the max is already at position `i`, it's already in place — skip both flips. |
| **(4)** `if max_idx != 0` | If the max is **not** at the front, record flip `max_idx + 1` and reverse `arr[0..max_idx]` to bring the max to `arr[0]`. |
| **(5)** Record flip `i + 1` | Reverse `arr[0..i]` to move `arr[0]` (the max) to its final position `arr[i]`. |

**Trace on Example 1:** `arr = [3, 2, 4, 1]`

| Round | i | Unsorted prefix | max_idx | Flip 1 | After Flip 1 | Flip 2 | After Flip 2 |
|-------|---|-----------------|---------|--------|--------------|--------|--------------|
| 1 | 3 | [3,2,4,1] | 2 | k=3 → reverse [3,2,4] | [4,2,3,1] | k=4 → reverse [4,2,3,1] | [1,3,2,4] |
| 2 | 2 | [1,3,2] | 1 | k=2 → reverse [1,3] | [3,1,2,4] | k=3 → reverse [3,1,2] | [2,1,3,4] |
| 3 | 1 | [2,1] | 0 | skip (max already at front) | — | k=2 → reverse [2,1] | [1,2,3,4] ✓ |

> Note: The actual output flips may differ from the example's `[4,2,4,3]` — both are valid as long as the array ends up sorted.

**Complexity:**
- **Time:** $O(n^2)$ — `n` rounds, each scanning up to `n` elements and doing an $O(n)$ reversal.
- **Space:** $O(n)$ — result list stores at most $2(n-1)$ flip values.
```

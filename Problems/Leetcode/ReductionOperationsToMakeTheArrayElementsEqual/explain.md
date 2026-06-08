## Problem

https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/description/

Given an integer array `nums`, your goal is to make all elements equal. One operation:
1. Find the **largest** value; if there are ties, pick the one at the **smallest index**.
2. Find the **next largest** value strictly smaller than the largest.
3. **Reduce** that element to the next largest value.

Return the **minimum number of operations** to make all elements equal.

**Constraints:**
- `1 <= nums.length <= 5 * 10^4`
- `1 <= nums[i] <= 5 * 10^4`

**Examples:**

| Input | Output | Why |
|---|---|---|
| `[5,1,3]` | `3` | 5→3 (1 op), 3→1 (1 op), 3→1 (1 op) |
| `[1,1,1]` | `0` | Already equal |
| `[1,1,2,2,3]` | `4` | 3→2 (1), 2→1 (1), 2→1 (1), 2→1 (1) |

---

## Observations

1. **The minimum target is always the global minimum.** Every other element must eventually be reduced to `min(nums)`. The specific "one step at a time" constraint means each element must pass through every distinct value between itself and the minimum.

2. **Each element's cost equals its rank in the sorted distinct values.** If the distinct values sorted ascending are `[v₀, v₁, v₂, …, vₖ]` (where `v₀` is the minimum), then every element equal to `vᵢ` needs exactly `i` operations — one per level it must descend through.

   For `[1,1,2,2,3]` → distinct sorted: `[1, 2, 3]`:
   - Elements equal to `1` → rank 0 → **0 ops each**
   - Elements equal to `2` → rank 1 → **1 op each** (×2 elements = 2 ops)
   - Elements equal to `3` → rank 2 → **2 ops each** (×1 element = 2 ops)
   - Total: 0 + 2 + 2 = **4** ✓

3. **No need to simulate.** Instead of actually running all the operations step by step, we can count directly: sort the array, group equal values, and accumulate.

4. **The "running count" trick.** When sorted in descending order and processed group by group, a running counter `count` naturally holds the total number of elements in all groups seen so far. Each time we cross a level boundary (transition to the next smaller group), every element accumulated so far needs exactly one more operation to cross that boundary — so we add `count` to the result.

---

## Solution

### Approach: Sort + Greedy Level Counting

```python
class Solution:
    def reductionOperations(self, nums: List[int]) -> int:
        n = len(nums)
        nums.sort(reverse=True)   # largest values first

        res = 0
        count = 0
        i = 0
        while i < n:
            # Scan across the current group of equal values
            j = i
            while j < n and nums[j] == nums[i]:
                count += 1
                j += 1

            i = j
            # If a lower level exists, every element processed so far
            # needs one more operation to descend to that next level
            if i < n:
                res += count

        return res
```

**Step-by-step walkthrough for `nums = [1,1,2,2,3]`:**

After `sort(reverse=True)`: `[3, 2, 2, 1, 1]`

| Outer `i` | Group scanned | `count` after group | Lower level exists? | `res` after step |
|:---------:|:-------------:|:-------------------:|:-------------------:|:----------------:|
| 0 | `[3]` (size 1) | 1 | Yes (`2` exists) | 0 + 1 = **1** |
| 1 | `[2, 2]` (size 2) | 3 | Yes (`1` exists) | 1 + 3 = **4** |
| 3 | `[1, 1]` (size 2) | 5 | No (end of array) | **4** (unchanged) |

**Answer: 4** ✓

**Why this is correct:**  
- The `3` (rank 2) crosses **two** level boundaries (3→2, 2→1). It is counted in `res` at both transitions: at the 3→2 boundary (`count=1`) and at the 2→1 boundary (`count=3`, which still includes the `3`). Total contribution: 1 + 1 = 2 ✓  
- Each `2` (rank 1) crosses **one** boundary (2→1). Each is counted once at the 2→1 boundary. Total contribution per `2`: 1 × 2 = 2 ✓  
- The `1`s (rank 0) are never counted because `i >= n` when we finish their group. ✓

### Complexity Analysis

| | Complexity |
|---|---|
| **Time** | O(n log n) — dominated by sorting |
| **Space** | O(1) extra — sorting in-place |

---

# Tags

`Array`, `Sorting`, `Greedy`

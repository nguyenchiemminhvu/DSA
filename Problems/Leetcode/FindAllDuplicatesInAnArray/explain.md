## Problem

https://leetcode.com/problems/find-all-duplicates-in-an-array/description/

Given an integer array `nums` of length `n` where all integers are in the range `[1, n]` and each integer appears **at most twice**, return an array of all integers that appear **twice**.

The algorithm must run in **O(n) time** and use only **constant auxiliary space** (excluding the output array).

**Examples:**
- `[4,3,2,7,8,2,3,1]` → `[2,3]`
- `[1,1,2]` → `[1]`
- `[1]` → `[]`

---

## Observations

1. **Values are index-like:** Every value `v` in `nums` satisfies `1 <= v <= n`, which means each value can directly map to an index in a size `n+1` auxiliary array.

2. **Frequency encoding without extra space (classic trick):** Since values are bounded by `n`, the classic O(n) / O(1) approach negates `nums[abs(v) - 1]` as a visited marker. If it's already negative when we visit it, `abs(v)` is a duplicate.

3. **The provided solution uses a different encoding trick:** Instead of negation, it adds `n` to `temp[val]` each time `val` is seen. After processing:
   - `temp[val] == n` → `val` appeared exactly once.
   - `temp[val] == 2*n` → `val` appeared exactly twice (a duplicate).
   - `temp[val] == 0` → `val` never appeared.

   A value is a duplicate when `temp[i] > n` (i.e., it was incremented at least twice, reaching `2*n`).

4. **Why `> n` works as the condition:** Each occurrence adds exactly `n`. One occurrence → `temp[val] = n` (not `> n`). Two occurrences → `temp[val] = 2*n` (which is `> n`). Since each value appears at most twice per the constraints, `temp[val]` is always either `0`, `n`, or `2*n`.

5. **Space complexity caveat:** The solution uses an auxiliary array `temp` of size `n+1`, which is **O(n) extra space** — not O(1). It satisfies the time constraint but not the strict space constraint. The true O(1) space solution uses in-place negation on `nums` itself.

---

## Solution Explanation

```python
class Solution:
    def findDuplicates(self, nums: List[int]) -> List[int]:
        n = len(nums)
        temp = [0] * (n + 1)       # frequency table indexed by value (1..n)
        for val in nums:
            temp[val] += n          # add n for each occurrence of val

        res = []
        for i, val in enumerate(temp):
            if val > n:             # val was seen twice: temp[i] == 2*n > n
                res.append(i)
        return res
```

**Step-by-step walkthrough** with `nums = [4,3,2,7,8,2,3,1]`, `n = 8`:

| Pass | Action | `temp` (indices 1–8) |
|------|--------|----------------------|
| val=4 | temp[4] += 8 | `[0,0,0,0,8,0,0,0,0]` |
| val=3 | temp[3] += 8 | `[0,0,0,8,8,0,0,0,0]` |
| val=2 | temp[2] += 8 | `[0,0,8,8,8,0,0,0,0]` |
| val=7 | temp[7] += 8 | `[0,0,8,8,8,0,0,8,0]` |
| val=8 | temp[8] += 8 | `[0,0,8,8,8,0,0,8,8]` |
| val=2 | temp[2] += 8 | `[0,0,16,8,8,0,0,8,8]` |
| val=3 | temp[3] += 8 | `[0,0,16,16,8,0,0,8,8]` |
| val=1 | temp[1] += 8 | `[0,8,16,16,8,0,0,8,8]` |

After the loop, indices where `temp[i] > 8` (i.e., `> n`) are `2` and `3` → output `[2, 3]`. ✓

**Time complexity:** O(n) — two linear passes.  
**Space complexity:** O(n) — for the `temp` array (violates the strict O(1) constraint).

> **True O(1) space alternative:** Use in-place negation — for each `val`, negate `nums[abs(val) - 1]`; if it's already negative, `abs(val)` is a duplicate. This modifies the input array in-place, using no extra space.

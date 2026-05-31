## Problem

https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/description/

Given an integer array `nums`, construct a 2D array such that:
- It contains **only** the elements of `nums` (all elements used, no extras).
- Each row contains **distinct** integers.
- The number of rows is **minimal**.

Return any valid result.

---

## Observations

1. **Row count equals max frequency.** An element that appears `k` times must go into `k` different rows (since each row requires distinct elements). Therefore, the minimum number of rows needed is exactly `max(frequency of any element)`.

2. **Each occurrence of a value goes to a different row.** On the first pass through all elements, each unique value contributes one element to row 0. On the second pass, each value that still has remaining occurrences contributes one element to row 1, and so on.

3. **Frequency counter drives the construction.** Using a `Counter` makes it easy to track remaining occurrences. One iteration over the counter per row naturally distributes one copy of each value per row.

4. **Constraint `1 <= nums[i] <= nums.length` bounds duplicates.** An element can appear at most `nums.length` times, so the number of rows is at most `nums.length`.

---

## Solution Explanation

```python
from collections import Counter

class Solution:
    def findMatrix(self, nums: list[int]) -> list[list[int]]:
        res = []
        counter = Counter(nums)
        while True:
            row = []
            for k, v in counter.items():
                if v > 0:
                    row.append(k)
                    counter[k] -= 1
            if not row:
                break
            res.append(row)
        return res
```

**Step-by-step:**

1. Build a frequency map (`Counter`) of all elements.
2. Repeatedly sweep through every key in the counter:
   - If the key still has remaining count (`v > 0`), place it in the current row and decrement its count.
3. After the sweep, if the row is non-empty, append it to the result and repeat.
4. Stop when a sweep produces an empty row — all counts have reached zero.

**Why this minimises rows:**  
Each sweep consumes exactly one occurrence of every distinct value that still has remaining copies. This is equivalent to processing the elements layer-by-layer in order of their frequency, which is the minimum possible since any value appearing `k` times cannot be packed into fewer than `k` rows.

**Complexity:**
- Time: `O(n * d)` where `n = len(nums)` and `d` = number of distinct values. In the worst case (all duplicates of one value) this is `O(n)` rows × `O(d)` per row = `O(n²)`.
- Space: `O(n)` for the counter and output.

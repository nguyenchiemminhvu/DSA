## Problem

https://leetcode.com/problems/minimum-capacity-box/description/

You are given an integer array `capacity`, where `capacity[i]` represents the capacity of the `i`th box, and an integer `itemSize` representing the size of an item.

The `i`th box can store the item if `capacity[i] >= itemSize`.

Return an integer denoting the **index of the box with the minimum capacity** that can store the item. If multiple such boxes exist, return the **smallest index**.

If no box can store the item, return `-1`.

**Constraints:**
- `1 <= capacity.length <= 100`
- `1 <= capacity[i] <= 100`
- `1 <= itemSize <= 100`

**Examples:**

```
Input: capacity = [1,5,3,7], itemSize = 3  →  Output: 2
Input: capacity = [3,5,4,3], itemSize = 2  →  Output: 0
Input: capacity = [4],       itemSize = 5  →  Output: -1
```

## Observations

- We need to find boxes that are **at least as large** as the item (`capacity[i] >= itemSize`).
- Among all valid boxes, we want the one with the **smallest capacity** (tightest fit).
- If there is a **tie** in capacity, prefer the **leftmost index** (smallest index).
- Since we only need to scan the array once, a single linear pass suffices — no sorting needed.
- The constraints are small (`n ≤ 100`), so even a brute-force O(n) scan is perfectly efficient.

## Solution

We use a single linear scan, maintaining two variables:
- `min_box`: the smallest valid capacity seen so far (initialized to `+∞`).
- `idx`: the index of that box (initialized to `-1`).

For each box `i`:
1. Skip it if `capacity[i] < itemSize` (can't fit the item).
2. If `capacity[i] < min_box`, update `min_box` and `idx`.  
   We use **strict less-than** (`<`), so ties keep the earlier (smaller) index — which satisfies the "smallest index" requirement automatically.

Return `idx` at the end.

```python
class Solution:
    def minimumIndex(self, arr: list[int], target: int) -> int:
        idx = -1
        min_box = float('inf')
        for i in range(len(arr)):
            if arr[i] >= target and arr[i] < min_box:
                min_box = arr[i]
                idx = i
        return idx
```

**Complexity:**
- Time: $O(n)$ — single pass over the array.
- Space: $O(1)$ — only two extra variables.

# Tags
`Array` `Linear Scan` `Easy`


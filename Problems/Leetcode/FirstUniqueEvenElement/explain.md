## Problem

https://leetcode.com/problems/first-unique-even-element/description/

Given an integer array `nums`, return the **first even integer** (earliest by array index) that appears **exactly once**. If no such integer exists, return `-1`.

**Example 1:**
```
Input:  nums = [3,4,2,5,4,6]
Output: 2
```
Both `2` and `6` are even and appear exactly once. `2` comes first, so the answer is `2`.

**Example 2:**
```
Input:  nums = [4,4]
Output: -1
```
No even integer appears exactly once.

**Constraints:**
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

## Observations

- We only care about **even** numbers (`val % 2 == 0`).
- Among those, we want the one with **frequency = 1**.
- We want the **earliest occurrence** by index, so we should scan the original array in order rather than iterating over a set or dictionary (which do not preserve insertion order reliably for this purpose).
- A single pass to build a frequency map, followed by a second linear scan of the original array, gives us the correct first-seen ordering in **O(n)** time.

## Solution

```python
from collections import Counter

class Solution:
    def firstUniqueEven(self, nums: list[int]) -> int:
        f = Counter(nums)
        for val in nums:
            if val % 2 == 0 and f[val] == 1:
                return val
        return -1
```

**Step-by-step:**

1. **Build a frequency map** — `Counter(nums)` counts how many times every element (odd or even) appears. This is O(n) time and O(n) space.
2. **Scan in original order** — iterate through `nums` left to right. For each element:
   - Check if it is even (`val % 2 == 0`).
   - Check if it appears exactly once (`f[val] == 1`).
   - If both conditions hold, return it immediately — this is the **first** such element by index.
3. **No match** — if the loop finishes without returning, no qualifying element exists, so return `-1`.

**Complexity:**
- Time: O(n) — one pass to count, one pass to scan.
- Space: O(n) — the frequency map stores at most n distinct values.

# Tags
`Array` `Hash Table` `Counting`


## Problem

https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/

Given an integer array `banned` and two integers `n` and `maxSum`, choose the maximum number of integers following these rules:
- The chosen integers must be in the range `[1, n]`.
- Each integer can be chosen at most once.
- The chosen integers must not appear in `banned`.
- The sum of the chosen integers must not exceed `maxSum`.

Return the maximum count of integers you can choose.

**Examples:**
- `banned = [1,6,5], n = 5, maxSum = 6` → `2` (choose 2 and 4, sum = 6)
- `banned = [1,2,3,4,5,6,7], n = 8, maxSum = 1` → `0`
- `banned = [11], n = 7, maxSum = 50` → `7` (choose 1–7, sum = 28)

**Constraints:**
- `1 <= banned.length <= 10^4`
- `1 <= banned[i], n <= 10^4`
- `1 <= maxSum <= 10^9`

## Observations

- To **maximize the count** of chosen integers, we should prefer **smaller values** first — they consume less of the `maxSum` budget, leaving room for more integers.
- This is a **greedy** strategy: iterate from `1` to `n` in ascending order, greedily picking each number if it is not banned and fits within the remaining budget.
- We can stop early once adding the next candidate would exceed `maxSum`.
- Use a **hash set** for O(1) banned-membership checks.

## Solution

Iterate `i` from `1` to `n`. For each `i`:
1. Skip if `i` is in the banned set.
2. Skip if `cur_sum + i > maxSum` (adding it would exceed the budget).
3. Otherwise, add `i` to the running sum and increment the count.

```python
class Solution:
    def maxCount(self, banned: List[int], n: int, limit: int) -> int:
        s = set(banned)        # O(b) space, O(1) lookup
        cur_sum = 0
        count = 0
        for i in range(1, n + 1):
            if i not in s and cur_sum + i <= limit:
                cur_sum += i
                count += 1
        return count
```

**Complexity:**
- Time: O(n + b), where b = `len(banned)` — one pass over `[1, n]` plus set construction.
- Space: O(b) for the banned set.

# Tags

greedy, hash-set


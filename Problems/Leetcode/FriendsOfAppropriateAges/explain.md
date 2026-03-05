# Friends Of Appropriate Ages

## Problem

https://leetcode.com/problems/friends-of-appropriate-ages/description/

There are `n` persons on a social media website. You are given an integer array `ages` where `ages[i]` is the age of the `i`-th person.

Person `x` will **not** send a friend request to person `y` (`x != y`) if **any** of the following conditions is true:

1. `age[y] <= 0.5 * age[x] + 7`
2. `age[y] > age[x]`
3. `age[y] > 100 && age[x] < 100`

Otherwise, `x` will send a friend request to `y`.

Note that if `x` sends a request to `y`, `y` does not necessarily send a request back. A person will not send a friend request to themselves.

Return the **total number** of friend requests made.

### Examples

**Example 1:**
```
Input:  ages = [16, 16]
Output: 2
Explanation: Both persons friend request each other.
```

**Example 2:**
```
Input:  ages = [16, 17, 18]
Output: 2
Explanation: 17 → 16, 18 → 17.
```

**Example 3:**
```
Input:  ages = [20, 30, 100, 110, 120]
Output: 3
Explanation: 110 → 100, 120 → 110, 120 → 100.
```

### Constraints
- `n == ages.length`
- `1 <= n <= 2 * 10^4`
- `1 <= ages[i] <= 120`

---

## Observations

1. **Condition 3 is redundant.** If `age[x] < 100` and `age[y] > 100`, then `age[y] > age[x]`, which is already blocked by condition 2. So condition 3 never adds any additional restriction.

2. **Invert the conditions to find when a request IS made.** Flipping all three "do NOT send" conditions, `x` sends a request to `y` if and only if:
   ```
   0.5 * age[x] + 7  <  age[y]  <=  age[x]
   ```

3. **The valid range can be empty.** For `age[y]` to satisfy `0.5 * age[x] + 7 < age[y] <= age[x]`, we need:
   ```
   0.5 * age[x] + 7  <  age[x]
   0.5 * age[x]      >  7
   age[x]            >  14
   ```
   So any person with `age[x] <= 14` (i.e., `age[x] < 15`) can never send any friend request. We can skip them entirely.

4. **Counting with binary search.** After sorting `ages`, for each person `x` with `age[x] >= 15`, the valid recipients are all `y` whose age falls in the half-open interval `(0.5 * age[x] + 7, age[x]]`. We can count them in `O(log n)` using binary search:
   - `upper_left`  = first index with `age > 0.5 * age[x] + 7`  (start of the valid window)
   - `upper_right` = first index with `age > age[x]`            (one past the end of the valid window)
   - Count = `upper_right - upper_left`, then subtract 1 to exclude `x` themselves (since `age[x]` is included in the window and `x != y`).

5. **Overall complexity.** Sorting is `O(n log n)`. The binary-search loop is `O(n log n)`. Age values are bounded by 120, so the effective distinct-age space is tiny, but the approach works for the general case.

---

## Solution

```python
class Solution:
    def numFriendRequests(self, ages: List[int]) -> int:
        ages.sort()
        n = len(ages)

        # Returns the first index where arr[index] > target  (standard upper_bound)
        def upper_bound(arr: List[int], target: int) -> int:
            left, right = 0, len(arr) - 1
            idx = len(arr)
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx

        res = 0
        for i in range(n):
            age = ages[i]
            if age < 15:           # valid range is empty for age <= 14
                continue

            # x sends to y iff  0.5*age + 7 < age[y] <= age
            left_threshold  = int(age * 0.5 + 7)   # lower bound (exclusive)
            upper_left  = upper_bound(ages, left_threshold)  # first idx where age[y] > threshold
            upper_right = upper_bound(ages, age)             # first idx where age[y] > age[x]

            # subtract 1 to exclude x sending to themselves
            res += max(0, (upper_right - upper_left) - 1)

        return res
```

**Walk-through on Example 3** — `ages = [20, 30, 100, 110, 120]` (already sorted):

| `age[x]` | threshold (`0.5x+7`) | valid window | recipients (excl. self) |
|----------|----------------------|--------------|-------------------------|
| 20       | 17                   | (17, 20]     | none (only self)        |
| 30       | 22                   | (22, 30]     | none (only self)        |
| 100      | 57                   | (57, 100]    | none (only self)        |
| 110      | 62                   | (62, 110]    | {100} → **1**           |
| 120      | 67                   | (67, 120]    | {100, 110} → **2**      |

Total = 3. ✓

---

# Tags

`Binary Search` `Sorting` `Array`


## Problem

https://leetcode.com/problems/arithmetic-subarrays/description/

A sequence is **arithmetic** if it has at least two elements and the difference between every two consecutive elements is the same.

Given an array `nums` of `n` integers and two arrays `l` and `r` each of length `m`, representing `m` range queries `[l[i], r[i]]`, return a boolean list `answer` where `answer[i]` is `true` if the subarray `nums[l[i]..r[i]]` can be **rearranged** to form an arithmetic sequence.

**Example:**
```
nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]
Output: [true, false, true]
- [4,6,5] → rearranged [4,5,6] ✓
- [4,6,5,9] → cannot form arithmetic sequence ✗
- [5,9,3,7] → rearranged [3,5,7,9] ✓
```

**Constraints:**
- `2 <= n <= 500`, `1 <= m <= 500`
- `0 <= l[i] < r[i] < n`
- `-10^5 <= nums[i] <= 10^5`

---

## Observations

1. **Rearrangement is allowed** — we don't need the subarray to already be sorted; we only need to check if its elements *can* form an arithmetic sequence.

2. **Key property of an arithmetic sequence of length `n`:**  
   If we sort the sequence, the common difference must be `d = (max - min) / (n - 1)`.  
   For `d` to be an integer, `(max - min)` must be divisible by `(n - 1)`.

3. **Checking without sorting (O(n) per query):**  
   Once we know `min`, `max`, and `d`, every valid element must be of the form `min + k*d` for some integer `k` in `[0, n-1]`. We can map each element to its expected index `k = (val - min) / d` and mark it as "seen". If any element fails the divisibility check, maps out of range, or causes a duplicate, the subarray is not arithmetic.

4. **Edge case — all elements equal (`d = 0`):**  
   Every element must equal `min`. Handled separately to avoid division by zero.

5. **Complexity:**  
   - Each query processes a subarray of length at most `n`, so each check is **O(n)**.  
   - Total: **O(m × n)**, which is at most `500 × 500 = 250,000` operations — well within limits.

---

## Solution Explanation

```python
class Solution:
    def checkArithmeticSubarrays(self, nums: List[int], l_query: List[int], r_query: List[int]) -> List[bool]:
        def check(arr: List[int], n: int) -> bool:
            mn, ma = min(arr), max(arr)

            # Step 1: The total range (ma - mn) must be evenly divisible
            # by (n - 1) to produce an integer common difference.
            if (ma - mn) % (n - 1) != 0:
                return False

            d = (ma - mn) // (n - 1)

            # Step 2: Special case — all elements are equal (d == 0).
            # Every value must be exactly mn.
            if d == 0:
                return all(val == mn for val in arr)

            # Step 3: Map each element to its expected position index k = (val - mn) / d.
            # A valid arithmetic sequence needs exactly one element at each index 0..n-1.
            seen = [False] * n
            for val in arr:
                sub_d = val - mn
                # Each element must sit exactly on a multiple of d
                if sub_d % d != 0:
                    return False
                idx = sub_d // d
                # Index must be in range and not already occupied (no duplicates)
                if idx < 0 or idx >= n or seen[idx]:
                    return False
                seen[idx] = True

            # Step 4: Every slot must be filled (all positions accounted for)
            return all(seen)

        res = []
        for i in range(len(l_query)):
            l, r = l_query[i], r_query[i]
            res.append(check(nums[l: r + 1], r - l + 1))
        return res
```

### Walk-through on Example 1

| Query | Subarray   | min | max | n | d         | Result |
|-------|------------|-----|-----|---|-----------|--------|
| 0     | [4, 6, 5]  | 4   | 6   | 3 | (6-4)/2=1 | ✓ indices {0,2,1} all unique |
| 1     | [4,6,5,9]  | 4   | 9   | 4 | (9-4)/3 → not integer | ✗ |
| 2     | [5,9,3,7]  | 3   | 9   | 4 | (9-3)/3=2 | ✓ indices {1,3,0,2} all unique |

### Why this avoids sorting

Sorting would cost **O(n log n)** per query. By leveraging the mathematical structure of arithmetic sequences — every element maps to a unique slot — we achieve **O(n)** per query using a boolean `seen` array, making the approach both simpler and faster.

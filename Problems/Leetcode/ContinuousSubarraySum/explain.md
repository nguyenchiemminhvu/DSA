## Problem

https://leetcode.com/problems/continuous-subarray-sum/description/

Given an integer array `nums` and an integer `k`, return `true` if `nums` has a **good subarray** or `false` otherwise.

A **good subarray** is a subarray where:
- its length is **at least two**, and
- the sum of the elements of the subarray is a **multiple of** `k`.

Note that `0` is always a multiple of `k`.

**Examples:**

```
Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a subarray of size 2 whose elements sum to 6.

Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23,2,6,4,7] sums to 42 = 7 × 6.

Input: nums = [23,2,6,4,7], k = 13
Output: false
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `0 <= nums[i] <= 10^9`
- `0 <= sum(nums[i]) <= 2^31 - 1`
- `1 <= k <= 2^31 - 1`

---

## Observations

1. **Subarray sum via prefix sums:** The sum of subarray `nums[i..j]` equals `prefix[j] - prefix[i-1]`. For this sum to be a multiple of `k`:
   $$(\text{prefix}[j] - \text{prefix}[i-1]) \bmod k = 0$$
   which simplifies to:
   $$\text{prefix}[j] \bmod k = \text{prefix}[i-1] \bmod k$$
   So we only need to track **prefix sum remainders mod k**.

2. **First-occurrence map:** Store the **earliest index** at which each remainder first appears. If the same remainder appears again at index `j`, the subarray between those two positions has a sum divisible by `k`. Storing the first occurrence maximises the potential subarray length.

3. **Length ≥ 2 check:** If remainder `rem` was first seen at index `p`, the subarray ending at index `j` with this remainder spans `nums[p+1..j]`, giving length `j - p`. We require `j - p >= 2`.

4. **Initialization `mp = {0: -1}`:** The empty prefix (before index 0) has sum 0 and remainder 0, logically placed at index `-1`. If remainder `0` reappears at index `j`, the subarray `nums[0..j]` has length `j - (-1) = j + 1 >= 2`, which is valid as long as `j >= 1`.

5. **Do not overwrite existing entries:** Only the first occurrence matters — it gives the longest (or equal-length) candidate subarray. Overwriting with a later index could shrink the length below 2 unnecessarily.

---

## Solution Explanation

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        s = 0
        mp = {0: -1}            # remainder 0 seen before index 0
        for i, val in enumerate(nums):
            s += val
            rem = s % k
            if rem in mp:
                if i - mp[rem] >= 2:    # subarray length is at least 2
                    return True
            else:
                mp[rem] = i             # record first occurrence only
        return False
```

**Step-by-step logic:**

- Maintain `s` as the running prefix sum and `rem = s % k` as its remainder.
- For each index `i`, check if `rem` has been seen before. If yes and the gap is at least 2, a good subarray exists.
- If `rem` is new, record `i` as its first occurrence and move on.

**Walkthrough on `nums = [23,2,4,6,7], k = 6`:**

| idx | val | s  | rem | rem in mp?   | length  | mp after                  |
|-----|-----|----|-----|--------------|---------|---------------------------|
| —   | —   | 0  | —   | —            | —       | {0:-1}                    |
| 0   | 23  | 23 | 5   | no           | —       | {0:-1, 5:0}               |
| 1   | 2   | 25 | 1   | no           | —       | {0:-1, 5:0, 1:1}          |
| 2   | 4   | 29 | 5   | yes, mp[5]=0 | 2-0=**2** ≥ 2 → **True** | |

Subarray `nums[1..2] = [2, 4]`, sum = 6 = 1 × 6 ✓

**Walkthrough on `nums = [23,2,6,4,7], k = 13`:**

| idx | val | s  | rem | rem in mp? | mp after                         |
|-----|-----|----|-----|------------|----------------------------------|
| —   | —   | 0  | —   | —          | {0:-1}                           |
| 0   | 23  | 23 | 10  | no         | {0:-1, 10:0}                     |
| 1   | 2   | 25 | 12  | no         | {0:-1, 10:0, 12:1}               |
| 2   | 6   | 31 | 5   | no         | {0:-1, 10:0, 12:1, 5:2}          |
| 3   | 4   | 35 | 9   | no         | {0:-1, 10:0, 12:1, 5:2, 9:3}     |
| 4   | 7   | 42 | 3   | no         | {0:-1, 10:0, 12:1, 5:2, 9:3, 3:4}|

No repeated remainder found → **False** ✓

**Complexity:**
- Time: $O(n)$ — single pass through the array
- Space: $O(\min(n, k))$ — at most `k` distinct remainders stored in the map

## Problem

https://leetcode.com/problems/binary-subarrays-with-sum/description/

Given a binary array `nums` and an integer `goal`, return the number of non-empty **subarrays** with a sum equal to `goal`.

A **subarray** is a contiguous part of the array.

**Examples:**

```
Input: nums = [1,0,1,0,1], goal = 2
Output: 4

Input: nums = [0,0,0,0,0], goal = 0
Output: 15
```

**Constraints:**
- `1 <= nums.length <= 3 * 10^4`
- `nums[i]` is either `0` or `1`
- `0 <= goal <= nums.length`

---

## Observations

1. **Subarray sum via prefix sums:** The sum of a subarray `nums[i..j]` equals `prefix[j] - prefix[i-1]`. So we need to count pairs where `prefix[j] - prefix[i-1] == goal`, i.e., `prefix[i-1] == prefix[j] - goal`.

2. **Prefix sum frequency map:** As we scan left to right maintaining a running prefix sum `cur_sum`, for each position we ask: *how many previous prefix sums equal `cur_sum - goal`?* Each such previous index defines a valid subarray ending at the current position.

3. **Initialize `mp[0] = 1`:** Before processing any element, the prefix sum is `0`. This seed handles subarrays that start from index `0` (i.e., when the entire prefix sums to `goal`).

4. **Binary values don't change the approach:** Although the array is binary (0 or 1), the prefix sum technique works for any non-negative integers. The binary constraint simply bounds the possible prefix sum range `[0, n]`.

---

## Solution Explanation

```python
class Solution:
    def numSubarraysWithSum(self, nums: List[int], goal: int) -> int:
        mp = {}
        mp[0] = 1       # empty prefix has sum 0

        res = 0
        cur_sum = 0
        for val in nums:
            cur_sum += val                          # extend prefix sum to current index
            if cur_sum - goal in mp:
                res += mp[cur_sum - goal]           # count valid starting points
            mp[cur_sum] = mp.get(cur_sum, 0) + 1   # record this prefix sum
        return res
```

**Step-by-step logic:**

- Maintain `cur_sum` as the prefix sum up to the current index.
- For each new `cur_sum`, we want subarrays ending here with sum `goal`. That means we need a previous prefix sum of `cur_sum - goal`.
- `mp` stores how many times each prefix sum has been seen so far. Adding `mp[cur_sum - goal]` to `res` counts all valid left boundaries at once.
- After querying, record `cur_sum` in `mp` for future iterations.

**Walkthrough on `nums = [1,0,1,0,1], goal = 2`:**

| idx | val | cur_sum | cur_sum - goal | mp lookup | res | mp after |
|-----|-----|---------|----------------|-----------|-----|----------|
| —   | —   | 0       | —              | —         | 0   | {0:1}    |
| 0   | 1   | 1       | -1             | not found | 0   | {0:1,1:1}|
| 1   | 0   | 1       | -1             | not found | 0   | {0:1,1:2}|
| 2   | 1   | 2       | 0              | mp[0]=1   | 1   | {0:1,1:2,2:1}|
| 3   | 0   | 2       | 0              | mp[0]=1   | 2   | {0:1,1:2,2:2}|
| 4   | 1   | 3       | 1              | mp[1]=2   | 4   | {0:1,1:2,2:2,3:1}|

Result: **4** ✓

**Complexity:**
- Time: $O(n)$ — single pass
- Space: $O(n)$ — prefix sum frequency map

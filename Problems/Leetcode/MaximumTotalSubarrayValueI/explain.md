## Problem

https://leetcode.com/problems/maximum-total-subarray-value-i/description

You are given an integer array `nums` of length `n` and an integer `k`.

Choose exactly `k` non-empty subarrays of `nums`. Subarrays may overlap, and the exact same subarray (same `l` and `r`) can be chosen more than once.

The **value** of a subarray `nums[l..r]` is defined as:

$$\text{value}(l, r) = \max(\text{nums}[l..r]) - \min(\text{nums}[l..r])$$

The **total value** is the sum of the values of all chosen subarrays.

Return the **maximum possible total value** you can achieve.

**Example 1:**
```
Input: nums = [1,3,2], k = 2
Output: 4
Explanation:
- Choose nums[0..1] = [1,3]: value = 3 - 1 = 2
- Choose nums[0..2] = [1,3,2]: value = 3 - 1 = 2
- Total = 2 + 2 = 4
```

**Example 2:**
```
Input: nums = [4,2,5,1], k = 3
Output: 12
Explanation:
- Choose nums[0..3] = [4,2,5,1]: value = 5 - 1 = 4
- Choose nums[0..3] again: value = 4
- Choose nums[2..3] = [5,1]: value = 4
- Total = 4 + 4 + 4 = 12
```

**Constraints:**
- `1 <= n == nums.length <= 5 * 10^4`
- `0 <= nums[i] <= 10^9`
- `1 <= k <= 10^5`

## Observations

1. **Value upper bound per subarray**: The value of any subarray `nums[l..r]` is bounded by:
   $$\text{value}(l, r) \leq \max(\text{nums}) - \min(\text{nums})$$
   This is because no subarray can contain elements outside of the global maximum and minimum of `nums`.

2. **The upper bound is always achievable**: The entire array `nums[0..n-1]` always contains both the global maximum and global minimum. Therefore, its value is exactly `max(nums) - min(nums)`.

3. **Repetition is allowed**: Since we can choose the same subarray multiple times, we are free to pick the highest-value subarray on every single one of our `k` choices.

4. **Greedy optimality**: To maximize the total, we simply pick the best single subarray (the one achieving `max(nums) - min(nums)`) exactly `k` times. There is no benefit to diversifying choices — any other subarray has a value ≤ this maximum.

5. **The answer is therefore**: 

$$\text{answer} = k \times \bigl(\max(\text{nums}) - \min(\text{nums})\bigr)$$

## Solution

**Key insight**: The maximum value of any subarray is `max(nums) - min(nums)`. Since the same subarray can be chosen multiple times, we always pick the best one `k` times.

**Time Complexity**: $O(n)$ — a single pass to find the global max and min.  
**Space Complexity**: $O(1)$ — no extra data structures needed.

```python
class Solution:
    def maxTotalValue(self, nums: List[int], k: int) -> int:
        return k * (max(nums) - min(nums))
```

**Walkthrough — Example 2** (`nums = [4,2,5,1]`, `k = 3`):
- `max(nums) = 5`, `min(nums) = 1`
- Best single subarray value = `5 - 1 = 4`
- Pick it 3 times → total = `3 × 4 = 12` ✓

## Tags

`array` `greedy` `math`

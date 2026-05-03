## Problem

https://leetcode.com/problems/max-number-of-k-sum-pairs/description

Given an integer array `nums` and an integer `k`, in one operation you can pick two numbers from the array whose sum equals `k` and remove both from the array. Return the maximum number of operations you can perform on the array.

**Example 1:**
```
Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Remove (1,4) → nums = [2,3]. Remove (2,3) → nums = []. Total: 2 operations.
```

**Example 2:**
```
Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Remove two 3's → nums = [1,4,3]. No more pairs sum to 6. Total: 1 operation.
```

**Constraints:**
- 1 ≤ nums.length ≤ 10⁵
- 1 ≤ nums[i] ≤ 10⁹
- 1 ≤ k ≤ 10⁹

## Observations

1. **Greedy pairing is safe**: Once we identify a pair that sums to k, we should remove it immediately. There's no benefit to skipping a valid pair, since removing it doesn't prevent finding other valid pairs.

2. **Sorting enables two-pointer technique**: After sorting, we can use two pointers starting from opposite ends. This allows us to efficiently find pairs in O(n log n) time.

3. **Two-pointer logic**:
   - If `nums[left] + nums[right] == k`: we found a pair, increment operations and move both pointers inward
   - If `nums[left] + nums[right] > k`: the sum is too large, move right pointer left to decrease the sum
   - If `nums[left] + nums[right] < k`: the sum is too small, move left pointer right to increase the sum

4. **Why this works**: After sorting, the array is monotonically increasing. When we have a mismatch, moving the pointers in the correct direction guarantees we explore all necessary combinations without redundancy.

## Solution

```python
class Solution:
    def maxOperations(self, nums: List[int], k: int) -> int:
        nums.sort()
        n = len(nums)
        left, right = 0, n - 1
        op = 0
        
        while left < right:
            s = nums[left] + nums[right]
            if s == k:
                op += 1
                left += 1
                right -= 1
            elif s > k:
                right -= 1
            else:
                left += 1
        
        return op
```

### Detailed Explanation

1. **Sorting Phase** (`nums.sort()`):
   - Time complexity: O(n log n)
   - Arranges numbers in ascending order, enabling the two-pointer approach

2. **Two-Pointer Initialization**:
   - `left = 0`: points to the smallest element
   - `right = n - 1`: points to the largest element
   - `op = 0`: counts successful operations

3. **Main Loop** (`while left < right`):
   - Calculate sum: `s = nums[left] + nums[right]`
   - **Case 1 - Exact match** (`s == k`):
     - Found a valid pair! Increment operation counter
     - Move both pointers inward to find the next pair
   - **Case 2 - Sum too large** (`s > k`):
     - Current sum exceeds target
     - Decrease sum by moving right pointer left (toward smaller numbers)
   - **Case 3 - Sum too small** (`s < k`):
     - Current sum below target
     - Increase sum by moving left pointer right (toward larger numbers)

4. **Time Complexity**: O(n log n) dominated by sorting; the two-pointer loop is O(n)
5. **Space Complexity**: O(1) or O(n) depending on sorting algorithm (in-place vs. non-in-place)

### Why Two-Pointer Works

After sorting, the array maintains the invariant that any element at index i is less than elements at indices greater than i. This means:
- If `nums[left] + nums[right] > k`, we must move right pointer left because **all** elements from `left` to `right-1` would also sum to more than k with `nums[left]`
- If `nums[left] + nums[right] < k`, we must move left pointer right because **all** elements from `left+1` to `right` would still sum to less than k with `nums[right]`

This guarantee ensures we don't miss any valid pairs.

# Tags

two-pointer, sorting, greedy


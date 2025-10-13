## Problem

https://leetcode.com/problems/minimum-operations-to-collect-elements/

```
You are given an array nums of positive integers and an integer k.

In one operation, you can remove the last element of the array and add it to your collection.

Return the minimum number of operations needed to collect elements 1, 2, ..., k.

Example 1:

Input: nums = [3,1,5,4,2], k = 2
Output: 4
Explanation: After 4 operations, we collect elements 2, 4, 5, and 1, in this order. Our collection contains elements 1 and 2. Hence, the answer is 4.

Example 2:

Input: nums = [3,1,5,4,2], k = 5
Output: 5
Explanation: After 5 operations, we collect elements 2, 4, 5, 1, and 3, in this order. Our collection contains elements 1 through 5. Hence, the answer is 5.

Example 3:

Input: nums = [3,2,5,3,1], k = 3
Output: 4
Explanation: After 4 operations, we collect elements 1, 3, 5, and 2, in this order. Our collection contains elements 1 through 3. Hence, the answer is 4.

Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= nums.length
1 <= k <= nums.length
The input is generated such that you can collect elements 1, 2, ..., k.
```

## Observations

1. **Problem Understanding**: We need to collect all elements from 1 to k by removing elements from the end of the array. The goal is to find the minimum number of operations (removals) needed.

2. **Key Insight**: Since we can only remove from the end, we must process elements in reverse order (from right to left). We need to track which elements from 1 to k we've already collected.

3. **Bit Manipulation Approach**: The solution uses a bitmask to efficiently track which elements we still need to collect:
   - `mask = (1 << k) - 1` creates a mask with k bits set to 1
   - Each bit position represents whether we still need to collect that element
   - When we collect element `x`, we clear bit `x-1` using `mask &= ~(1 << (x-1))`

4. **Termination Condition**: When `mask` becomes 0, all required elements have been collected.

5. **Edge Cases**: 
   - Elements greater than k are ignored (we don't need them)
   - Duplicate elements within range [1,k] are processed but don't affect the mask after first occurrence

## Solution

1. **Initialize**: 
   - `count = 0` tracks operations
   - `mask = (1 << k) - 1` creates bitmask with k bits set (e.g., k=3 → mask=111₂=7)

2. **Process elements from right to left**:
   - Remove last element with `nums.pop()`
   - If element is in range [1,k], clear corresponding bit in mask
   - Increment operation counter

3. **Check completion**: 
   - If mask becomes 0, all elements [1,k] have been collected
   - Return the operation count

**Example Walkthrough** (nums=[3,1,5,4,2], k=2):
- Initial: mask = 11₂ = 3, count = 0
- Pop 2: mask = 11₂ & ~01₂ = 10₂, count = 1
- Pop 4: mask = 10₂ (no change, 4 > k), count = 2  
- Pop 5: mask = 10₂ (no change, 5 > k), count = 3
- Pop 1: mask = 10₂ & ~10₂ = 00₂, count = 4
- mask = 0, return 4

**Time Complexity**: O(n) where n is the number of operations needed
**Space Complexity**: O(1) using only constant extra space

**Why This Works**: The bitmask elegantly tracks which elements we still need while processing elements in the required order (from end to start).

## Tags

array, bit manipulation
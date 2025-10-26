## Problem

https://leetcode.com/problems/wiggle-sort-ii/

```
Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

You may assume the input array always has a valid answer.

Example 1:

Input: nums = [1,5,1,1,6,4]
Output: [1,6,1,5,1,4]
Explanation: [1,4,1,5,1,6] is also accepted.

Example 2:

Input: nums = [1,3,2,2,3,1]
Output: [2,3,1,3,1,2]

Constraints:

1 <= nums.length <= 5 * 104
0 <= nums[i] <= 5000
It is guaranteed that there will be an answer for the given input nums.
 

Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra space?
```

## Observations

1. **Pattern Analysis**: The wiggle sort requires alternating pattern where even indices have smaller values than their adjacent odd indices: `nums[0] < nums[1] > nums[2] < nums[3] > nums[4]...`

2. **Key Insight**: After sorting the array, we need to strategically place elements to avoid adjacent equal values while maintaining the wiggle pattern.

3. **Two-Part Division**: The sorted array can be divided into two parts:
   - Smaller half: elements from index 0 to `(n+1)//2 - 1`
   - Larger half: elements from index `(n+1)//2` to `n-1`

4. **Reverse Placement Strategy**: To avoid conflicts with duplicate elements, we place elements from both halves in reverse order:
   - Small elements (reversed) go to even positions (0, 2, 4, ...)
   - Large elements (reversed) go to odd positions (1, 3, 5, ...)

5. **Why Reverse Order Works**: Consider duplicates at the boundary between small and large halves. By placing them in reverse order, we maximize the distance between potentially equal elements.

6. **Example Walkthrough**:
   ```
   Input: [1,5,1,1,6,4]
   Sorted: [1,1,1,4,5,6]
   Small half: [1,1,1] → reversed: [1,1,1]
   Large half: [4,5,6] → reversed: [6,5,4]
   Result: [1,6,1,5,1,4] (small at even, large at odd)
   ```

## Solution

**Time Complexity**: O(n log n) due to sorting
**Space Complexity**: O(n) for the temporary arrays `small` and `large`

**Algorithm Steps**:
1. Sort the input array to arrange elements in ascending order
2. Divide the sorted array into two halves at position `(n+1)//2`
3. Reverse both halves to handle duplicate elements optimally
4. Place reversed smaller half at even indices (0, 2, 4, ...)
5. Place reversed larger half at odd indices (1, 3, 5, ...)

**Why This Works**:
- The sorted array ensures that elements in the first half are ≤ elements in the second half
- Reversing prevents adjacent duplicates that could violate the wiggle condition
- Even-odd placement naturally creates the required alternating pattern

## Tags

array, sorting, greedy
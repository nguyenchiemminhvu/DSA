## Problem

https://leetcode.com/problems/partition-array-into-three-parts-with-equal-sum/

```
Given an array of integers arr, return true if we can partition the array into three non-empty parts with equal sums.

Formally, we can partition the array if we can find indexes i + 1 < j with (arr[0] + arr[1] + ... + arr[i] == arr[i + 1] + arr[i + 2] + ... + arr[j - 1] == arr[j] + arr[j + 1] + ... + arr[arr.length - 1])

Example 1:

Input: arr = [0,2,1,-6,6,-7,9,1,2,0,1]
Output: true
Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1

Example 2:

Input: arr = [0,2,1,-6,6,7,9,-1,2,0,1]
Output: false

Example 3:

Input: arr = [3,3,6,5,-2,2,5,1,-9,4]
Output: true
Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4

Constraints:

3 <= arr.length <= 5 * 10^4
-10^4 <= arr[i] <= 10^4
```

## Observations

1. **Key Insight**: For an array to be partitioned into three equal-sum parts, the total sum must be divisible by 3.

2. **Prefix Sum Approach**: We can use prefix sums to efficiently check partition points. If we find two positions where:
   - First position has sum = total_sum/3
   - Second position has sum = 2*total_sum/3
   Then we have a valid partition.

3. **Critical Conditions**:
   - Total sum must be divisible by 3 (otherwise impossible)
   - Each part must be non-empty (need at least one element in each)
   - Need to find valid cut points i and j where i+1 < j

4. **Edge Cases**:
   - Arrays with length < 3 (impossible to partition)
   - Arrays where sum is not divisible by 3
   - Cases where we can find the sum targets but not with proper spacing

5. **Optimization**: By converting to prefix sums in-place and using index search, we avoid nested loops and achieve better performance.

## Solution

### Algorithm Overview

The solution uses a **prefix sum + two-phase search** approach:

1. **Convert to prefix sums**: Transform the array into cumulative sums
2. **Check divisibility**: Verify total sum is divisible by 3
3. **Find partition points**: Use index search to locate valid cut positions

### Key Implementation Details

**Prefix Sum Conversion:**
- `arr[i] += arr[i-1]` converts original array to prefix sums
- After conversion: `arr[i]` = sum of elements from index 0 to i

**Partition Logic:**
- First part: indices 0 to `first_cut` (sum = target)
- Second part: indices `first_cut+1` to `second_cut` (sum = target)
- Third part: indices `second_cut+1` to end (sum = target)

**Search Strategy:**
- Use `arr.index(target)` to find first occurrence of target sum
- After finding first cut, search remaining array for `target * 2`
- This ensures we find the second partition point correctly

**Non-empty Validation:**
- `found < (len(arr) - 1)` ensures third part has at least one element
- The slicing `arr[found + 1:]` ensures second part starts after first cut

### Example Walkthrough

**Input:** `arr = [0,2,1,-6,6,-7,9,1,2,0,1]`

1. **Prefix sums:** `[0,2,3,-3,3,-4,5,6,8,8,9]`
2. **Total sum:** `9`, `target = 9/3 = 3`
3. **First cut:** Found at index 2 (prefix sum = 3)
4. **Remaining array:** `[-3,3,-4,5,6,8,8,9]` (indices 3-10)
5. **Second cut:** Look for sum = 6, found at index 7 (original index 9)
6. **Validation:** Third part `[8,9]` is non-empty ✓

**Result:** `true` (parts: [0,2,1], [-6,6,-7,9,1], [2,0,1])

### Time & Space Complexity

- **Time:** O(n) - single pass for prefix sums + two linear searches
- **Space:** O(1) - modifies input array in-place

**Note:** The solution modifies the input array. If preservation is needed, create a copy first.

## Tags

`Array` `Prefix Sum` `Greedy` `Math`


## Problem

https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/

```
You are given an integer array nums. In one operation, you can add or subtract 1 from any element of nums.

Return the minimum number of operations to make all elements of nums divisible by 3.

Example 1:

Input: nums = [1,2,3,4]

Output: 3

Explanation:

All array elements can be made divisible by 3 using 3 operations:

Subtract 1 from 1.
Add 1 to 2.
Subtract 1 from 4.

Example 2:

Input: nums = [3,6,9]

Output: 0

Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= 50
```

## Observations

1. **Goal**: Make all elements divisible by 3 with minimum operations
2. **Operations allowed**: Add or subtract 1 from any element
3. **Key insight**: For any number, we need to find the minimum distance to the nearest multiple of 3

For any number `n`, there are only 3 possible remainders when divided by 3:
- `n % 3 = 0`: Already divisible by 3, no operations needed
- `n % 3 = 1`: We can subtract 1 to make it divisible by 3 (1 operation)
- `n % 3 = 2`: We can add 1 to make it divisible by 3 (1 operation)

The minimum operations for each number is `min(remainder, 3 - remainder)`:
- If remainder is 0: `min(0, 3) = 0` operations
- If remainder is 1: `min(1, 2) = 1` operation (subtract 1)
- If remainder is 2: `min(2, 1) = 1` operation (add 1)

## Solution

```python
class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        return sum(min(val % 3, 3 - (val % 3)) for val in nums)
```

**Explanation:**

1. For each number `val` in the array, calculate `val % 3` to get the remainder
2. The minimum operations needed is `min(val % 3, 3 - (val % 3))`:
   - `val % 3` represents operations needed by subtracting (moving to lower multiple of 3)
   - `3 - (val % 3)` represents operations needed by adding (moving to higher multiple of 3)
3. Sum up all the minimum operations for each element

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Example walkthrough:**
- `nums = [1,2,3,4]`
- For 1: `min(1 % 3, 3 - (1 % 3)) = min(1, 2) = 1`
- For 2: `min(2 % 3, 3 - (2 % 3)) = min(2, 1) = 1`  
- For 3: `min(3 % 3, 3 - (3 % 3)) = min(0, 3) = 0`
- For 4: `min(4 % 3, 3 - (4 % 3)) = min(1, 2) = 1`
- Total: 1 + 1 + 0 + 1 = 3 operations

## Tags

array
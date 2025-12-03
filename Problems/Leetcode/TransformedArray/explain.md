## Problem

https://leetcode.com/problems/transformed-array/description/

```
You are given an integer array nums that represents a circular array. Your task is to create a new array result of the same size, following these rules:

For each index i (where 0 <= i < nums.length), perform the following independent actions:
- If nums[i] > 0: Start at index i and move nums[i] steps to the right in the circular array. Set result[i] to the value of the index where you land.
- If nums[i] < 0: Start at index i and move abs(nums[i]) steps to the left in the circular array. Set result[i] to the value of the index where you land.
- If nums[i] == 0: Set result[i] to nums[i].

Return the new array result.

Note: Since nums is circular, moving past the last element wraps around to the beginning, and moving before the first element wraps back to the end.

Example 1:
Input: nums = [3,-2,1,1]
Output: [1,1,1,3]

Example 2:
Input: nums = [-1,4,-1]
Output: [-1,-1,4]

Constraints:
- 1 <= nums.length <= 100
- -100 <= nums[i] <= 100
```

## Observations

1. **Circular Array Movement**: The array wraps around, so we need to handle indices that go beyond the array bounds using modulo arithmetic.

2. **Three Cases to Handle**:
   - `nums[i] > 0`: Move right (forward) by `nums[i]` steps
   - `nums[i] < 0`: Move left (backward) by `abs(nums[i])` steps
   - `nums[i] == 0`: Stay at the same position

3. **Index Calculation**:
   - For positive movement: `(i + nums[i]) % n`
   - For negative movement: `(i + nums[i]) % n` (nums[i] is already negative)
   - The key insight is that both cases can be unified with the same formula

4. **Handling Negative Indices**:
   - When moving left, `(i + nums[i])` might become negative
   - Adding `n` before taking modulo ensures we get a positive result
   - Formula: `((i + nums[i]) + n) % n` works for all cases

## Solution

```python
class Solution:
    def constructTransformedArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        return [nums[((i + nums[i]) + n) % n] for i in range(n)]
```

### Explanation

**Key Formula**: `((i + nums[i]) + n) % n`

This elegant formula handles all three cases:

1. **When `nums[i] > 0` (move right)**:
   - Example: `i=0, nums[i]=3, n=4`
   - New index: `((0 + 3) + 4) % 4 = 7 % 4 = 3` ✓

2. **When `nums[i] < 0` (move left)**:
   - Example: `i=0, nums[i]=-1, n=3`
   - New index: `((0 + (-1)) + 3) % 3 = 2 % 3 = 2` ✓
   - The `+n` ensures we don't get negative indices before modulo

3. **When `nums[i] == 0` (stay)**:
   - Example: `i=2, nums[i]=0, n=5`
   - New index: `((2 + 0) + 5) % 5 = 7 % 5 = 2` ✓

**Why add `n` before modulo?**
- When `nums[i]` is negative and `abs(nums[i]) > i`, the sum `i + nums[i]` becomes negative
- Adding `n` shifts the value into positive range
- The modulo operation still gives the correct circular index
- Example: `i=1, nums[i]=-5, n=4`
  - Without `+n`: `(1 + (-5)) % 4 = -4 % 4 = 0` (Python's modulo handles this correctly, but adding n is more universal)
  - With `+n`: `((1 + (-5)) + 4) % 4 = 0 % 4 = 0` ✓

**Time Complexity**: O(n) - Single pass through the array  
**Space Complexity**: O(n) - For the result array (O(1) if we don't count the output)

### Alternative Solution (More Explicit)

```python
class Solution:
    def constructTransformedArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        result = []
        for i in range(n):
            if nums[i] == 0:
                result.append(nums[i])
            else:
                new_index = (i + nums[i]) % n
                result.append(nums[new_index])
        return result
```

This version is more readable but functionally equivalent since Python's modulo operator handles negative numbers correctly.

# Tags

#array #modulo-arithmetic #circular-array #simulation


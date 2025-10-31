## Problem

https://leetcode.com/problems/compute-alternating-sum/description/

```
You are given an integer array nums.

The alternating sum of nums is the value obtained by adding elements at even indices and subtracting elements at odd indices. That is, nums[0] - nums[1] + nums[2] - nums[3]...

Return an integer denoting the alternating sum of nums.

Example 1:

Input: nums = [1,3,5,7]

Output: -4

Explanation:

Elements at even indices are nums[0] = 1 and nums[2] = 5 because 0 and 2 are even numbers.
Elements at odd indices are nums[1] = 3 and nums[3] = 7 because 1 and 3 are odd numbers.
The alternating sum is nums[0] - nums[1] + nums[2] - nums[3] = 1 - 3 + 5 - 7 = -4.

Example 2:

Input: nums = [100]

Output: 100

Explanation:

The only element at even indices is nums[0] = 100 because 0 is an even number.
There are no elements on odd indices.
The alternating sum is nums[0] = 100.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Pattern Recognition**: The problem asks for an alternating sum where we add elements at even indices and subtract elements at odd indices.
   - Pattern: `nums[0] - nums[1] + nums[2] - nums[3] + nums[4] - nums[5] + ...`
   - This can be rewritten as: `(+1) * nums[0] + (-1) * nums[1] + (+1) * nums[2] + (-1) * nums[3] + ...`

2. **Sign Pattern**: The sign alternates between +1 and -1 starting with +1:
   - Index 0: +1 (positive)
   - Index 1: -1 (negative)
   - Index 2: +1 (positive)
   - Index 3: -1 (negative)
   - And so on...

3. **Simple Iteration**: We can iterate through the array once and keep track of the current sign, multiplying each element by the appropriate sign and adding to the result.

4. **Edge Cases**: 
   - Single element array: Just return that element (positive sign)
   - Empty array: Not possible due to constraints (1 <= nums.length <= 100)

## Solution

1. **Initialize Variables**:
   - `res = 0`: Accumulator for the alternating sum
   - `sign = 1`: Current sign (starts positive for index 0)

2. **Iterate Through Array**:
   - For each element `val` in `nums`:
     - Multiply `val` by current `sign` and add to `res`
     - Flip the sign by multiplying by -1 (`sign *= -1`)

3. **Return Result**: Return the accumulated sum

**Time Complexity**: O(n) - Single pass through the array
**Space Complexity**: O(1) - Only using constant extra space

**Example Walkthrough** (nums = [1,3,5,7]):
- i=0: val=1, sign=1 → res = 0 + (1*1) = 1, sign becomes -1
- i=1: val=3, sign=-1 → res = 1 + (3*-1) = -2, sign becomes 1  
- i=2: val=5, sign=1 → res = -2 + (5*1) = 3, sign becomes -1
- i=3: val=7, sign=-1 → res = 3 + (7*-1) = -4, sign becomes 1
- Result: -4 ✓

## Tags

array
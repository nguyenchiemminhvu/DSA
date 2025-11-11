## Problem

https://leetcode.com/problems/ant-on-the-boundary/description/

```
An ant is on a boundary. It sometimes goes left and sometimes right.

You are given an array of non-zero integers nums. The ant starts reading nums from the first element of it to its end. At each step, it moves according to the value of the current element:

If nums[i] < 0, it moves left by -nums[i] units.
If nums[i] > 0, it moves right by nums[i] units.
Return the number of times the ant returns to the boundary.

Notes:

There is an infinite space on both sides of the boundary.
We check whether the ant is on the boundary only after it has moved |nums[i]| units. In other words, if the ant crosses the boundary during its movement, it does not count.

Example 1:

Input: nums = [2,3,-5]
Output: 1
Explanation: After the first step, the ant is 2 steps to the right of the boundary.
After the second step, the ant is 5 steps to the right of the boundary.
After the third step, the ant is on the boundary.
So the answer is 1.

Example 2:

Input: nums = [3,2,-3,-4]
Output: 0
Explanation: After the first step, the ant is 3 steps to the right of the boundary.
After the second step, the ant is 5 steps to the right of the boundary.
After the third step, the ant is 2 steps to the right of the boundary.
After the fourth step, the ant is 2 steps to the left of the boundary.
The ant never returned to the boundary, so the answer is 0.

Constraints:

1 <= nums.length <= 100
-10 <= nums[i] <= 10
nums[i] != 0
```

## Observations

1. **Position Tracking**: The ant starts at position 0 (the boundary). We need to track its cumulative position after each move.

2. **Movement Rules**: 
   - Positive values move the ant to the right
   - Negative values move the ant to the left
   - The distance moved is the absolute value of the number

3. **Boundary Detection**: The ant returns to the boundary when its cumulative position equals 0.

4. **Running Sum**: This is essentially a running sum problem where we count how many times the running sum equals 0.

5. **Simple Simulation**: We don't need complex data structures - just simulate the ant's movement step by step.

## Solution

**Algorithm**: Cumulative Sum with Zero Count

**Approach**:
1. Initialize a `pivot` variable to track the ant's current position (starts at 0)
2. Initialize a `count` variable to count boundary returns
3. For each number in the array:
   - Add the number to `pivot` (this simulates the ant's movement)
   - If `pivot` equals 0, increment `count` (ant returned to boundary)
4. Return the total count

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Key Insights**:
- The ant's position at any step is the cumulative sum of all previous moves
- We only care about when this cumulative sum equals 0 (boundary position)
- The problem reduces to counting zeros in the prefix sum array

**Example Walkthrough** (nums = [2,3,-5]):
- Step 1: pivot = 0 + 2 = 2 (ant is 2 steps right)
- Step 2: pivot = 2 + 3 = 5 (ant is 5 steps right) 
- Step 3: pivot = 5 + (-5) = 0 (ant returns to boundary) → count = 1

**Example Walkthrough** (nums = [3,2,-3,-4]):
- Step 1: pivot = 0 + 3 = 3 (ant is 3 steps right)
- Step 2: pivot = 3 + 2 = 5 (ant is 5 steps right)
- Step 3: pivot = 5 + (-3) = 2 (ant is 2 steps right)
- Step 4: pivot = 2 + (-4) = -2 (ant is 2 steps left)
- Never returns to 0 → count = 0

# Tags

`Array` `Simulation` `Prefix Sum` `Easy`


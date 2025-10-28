## Problem

https://leetcode.com/problems/make-array-elements-equal-to-zero/description/

```
You are given an integer array nums.

Start by selecting a starting position curr such that nums[curr] == 0, and choose a movement direction of either left or right.

After that, you repeat the following process:

If curr is out of the range [0, n - 1], this process ends.
If nums[curr] == 0, move in the current direction by incrementing curr if you are moving right, or decrementing curr if you are moving left.
Else if nums[curr] > 0:
Decrement nums[curr] by 1.
Reverse your movement direction (left becomes right and vice versa).
Take a step in your new direction.
A selection of the initial position curr and movement direction is considered valid if every element in nums becomes 0 by the end of the process.

Return the number of possible valid selections.

Example 1:

Input: nums = [1,0,2,0,3]

Output: 2

Explanation:

The only possible valid selections are the following:

Choose curr = 3, and a movement direction to the left.
[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,1,0,3] -> [1,0,1,0,3] -> [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,0,0,2] -> [1,0,0,0,2] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,0].
Choose curr = 3, and a movement direction to the right.
[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,2,0,2] -> [1,0,2,0,2] -> [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,1,0,1] -> [1,0,1,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [0,0,0,0,0].

Example 2:

Input: nums = [2,3,4,0,4,1,0]

Output: 0

Explanation:

There are no possible valid selections.

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
There is at least one element i where nums[i] == 0.
```

## Observations

1. **Starting Position**: We can only start at positions where `nums[i] == 0`. This is a constraint given in the problem.

2. **Movement Rules**: 
   - If current element is 0: continue in the same direction
   - If current element > 0: decrement it by 1, reverse direction, then move

3. **Success Condition**: All elements in the array must become 0 by the end of the simulation.

4. **Brute Force Approach**: For each starting position with value 0, try both directions (left and right) and simulate the entire process.

5. **Key Insight**: The problem requires us to simulate the movement process completely for each valid starting position and direction combination.

6. **Boundary Conditions**: The process ends when we move out of array bounds `[0, n-1]`.

7. **State Changes**: Each simulation modifies the array, so we need a fresh copy for each attempt.

## Solution

**Approach: Simulation**

The solution uses a brute force simulation approach:

1. **Helper Function `moving(start_idx, direction)`**:
   - Creates a copy of the original array to avoid modifying the input
   - Simulates the movement process starting from `start_idx` with given `direction`
   - Returns `True` if all elements become 0, `False` otherwise

2. **Main Logic**:
   - Iterate through all positions in the array
   - For each position with value 0, try both directions (-1 for left, 1 for right)
   - Count valid selections that result in all zeros

**Simulation Process**:
- Start at the given index with the given direction
- While within bounds:
  - If current element is 0: move in current direction
  - If current element > 0: decrement it, reverse direction, then move
- Check if all elements are 0 at the end

**Time Complexity**: O(n² × max_value) where n is array length and max_value is the maximum element value. In worst case, we might need to traverse the array multiple times for each starting position.

**Space Complexity**: O(n) for creating array copies during simulation.

**Example Walkthrough** (nums = [1,0,2,0,3]):
- Position 1 (value 0): Try left and right - both might fail
- Position 3 (value 0): Try left and right - both succeed in this case
- Total valid selections: 2

## Tags


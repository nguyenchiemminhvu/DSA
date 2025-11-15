## Problem

https://leetcode.com/problems/minimum-moves-to-equal-array-elements-iii/description/

```
You are given an integer array nums.

In one move, you may increase the value of any single element nums[i] by 1.

Return the minimum total number of moves required so that all elements in nums become equal.

Example 1:

Input: nums = [2,1,3]

Output: 3

Explanation:

To make all elements equal:

Increase nums[0] = 2 by 1 to make it 3.
Increase nums[1] = 1 by 1 to make it 2.
Increase nums[1] = 2 by 1 to make it 3.
Now, all elements of nums are equal to 3. The minimum total moves is 3.

Example 2:

Input: nums = [4,4,5]

Output: 2

Explanation:

To make all elements equal:

Increase nums[0] = 4 by 1 to make it 5.
Increase nums[1] = 4 by 1 to make it 5.
Now, all elements of nums are equal to 5. The minimum total moves is 2.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Only increment operations allowed**: We can only increase elements by 1, never decrease them.

2. **Target value must be the maximum**: Since we can only increment values, all elements must eventually equal the maximum value in the array. Any target less than the maximum would be impossible to achieve.

3. **Minimum moves calculation**: For each element, the number of moves required is `max_value - current_value`. The total moves is the sum of all individual moves needed.

4. **Greedy approach works**: We don't need to consider any complex strategies. Simply bringing every element up to the maximum value gives us the optimal solution.

5. **Time complexity**: O(n) for finding max + O(n) for calculating moves = O(n)
6. **Space complexity**: O(1) - only using a few variables

## Solution

1. **Find the target**: `top = max(nums)` - Since we can only increment, the final value for all elements must be the maximum value in the array.

2. **Calculate moves for each element**: For each element `val`, we need `top - val` moves to bring it up to `top`.

3. **Sum all moves**: Add up all the individual moves required.

**Example walkthrough with nums = [2,1,3]:**
- Maximum value: 3
- Moves needed: (3-2) + (3-1) + (3-3) = 1 + 2 + 0 = 3

**Why this is optimal:**
- We cannot make any element smaller (only increments allowed)
- We must make all elements equal to some target value
- The minimum possible target is the current maximum
- Therefore, this greedy approach gives the minimum total moves

# Tags

Array, Math, Greedy

